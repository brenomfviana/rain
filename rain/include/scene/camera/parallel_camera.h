#ifndef _PARALLEL_CAMERA_H_
#define _PARALLEL_CAMERA_H_

#include "camera.h"

using namespace utils;

/*!
 * This class respresents a perspective camera.
 */
class ParallelCamera : public Camera {

    public:
        //
        Vec3::RealType top;
        Vec3::RealType left;
        Vec3::RealType right;
        Vec3::RealType bottom;
        Vec3 w, u, v;

        /*!
         * Camera constructor.
         */
        ParallelCamera(Point3 look_from, Point3 look_at, Vec3 vup, Vec3::RealType top,
                Vec3::RealType left, Vec3::RealType right, Vec3::RealType bottom) :
                Camera(look_from), top(top), left(left), right(right), bottom(bottom) {
            w = unitVector(look_from - look_at);
            u = unitVector(cross(vup, w));
            v = cross(w, u);
        }

        Ray getRay(Vec3::RealType u, Vec3::RealType v) const {
            //
            u = left   + (right - left) * u;
            v = bottom + (top - bottom) * (1 - v);
            Vec3 o = origin + u * this->u + v * this->v;
            return Ray(o, -w);
        };
};

#endif /* _PARALLEL_CAMERA_H_ */

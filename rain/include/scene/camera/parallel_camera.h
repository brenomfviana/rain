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
        Vec3 w;
        Vec3 u;
        Vec3 v;

        /*!
         * Parallel camera constructor.
         */
        ParallelCamera(Point3 look_from, Point3 look_at, Vec3 vup, Vec3::RealType top,
                Vec3::RealType left, Vec3::RealType right, Vec3::RealType bottom);

        /*!
         * Parallel camera destructor.
         */
        ~ParallelCamera();

        Ray get_ray(Vec3::RealType u, Vec3::RealType v) const;
};

#endif /* _PARALLEL_CAMERA_H_ */

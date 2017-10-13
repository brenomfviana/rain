#ifndef _PERSPECTIVE_CAMERA_H_
#define _PERSPECTIVE_CAMERA_H_

#include <cmath>
#include "camera.h"

using namespace utils;

/*!
 * This class respresents a perspective camera.
 */
class PerspectiveCamera : public Camera {

    public:
		// Lower left corner of the view plane
		Point3 llc;
		// Horizontal dimension of the view plane
	    Vec3 horizontal;
		// Vertical dimension of the view plane
	    Vec3 vertical;
        //
        Vec3 u, v, w;
        //
        Vec3::RealType lens_radius;

        /*!
         * Camera constructor.
         *
         * @param origin The camera's origin
         * @param vfov The vertical field of view
         * @param aspect_ratio Aspect ratio
         * @param fd The focal distance of the view plane
         */
        PerspectiveCamera(Point3 look_from, Point3 look_at, Vec3 vup,
            Vec3::RealType vfov, Vec3::RealType aspect_ratio, Vec3::RealType aperture,
            Vec3::RealType fd) : Camera(look_from) {
                lens_radius = aperture / 2;
                Vec3::RealType theta = ((vfov * M_PI) / 180.f);
                float half_heigth = std::tan(theta / 2);
                float half_width = aspect_ratio * half_heigth;
                w = unitVector(look_from - look_at);
                u = unitVector(cross(vup, w));
                v = cross(w, u);
                // fd = (look_from - look_at).length();
                llc = look_from - (half_width * fd * u) - (half_heigth * fd  * v) - w * fd;
                horizontal = 2 * half_width  * fd * u;
                vertical   = 2 * half_heigth * fd * v;
        }

        Ray getRay(Vec3::RealType u, Vec3::RealType v) const {
            Vec3 rd = lens_radius * randomInUnitDisk();
            Point3 p = (llc + (u * horizontal) + (v * vertical));
            Vec3 offset = (this->u * rd.x()) + (this->v * rd.y());
            return Ray(origin + offset, p - origin - offset);
        };

    private:
        inline Vec3 randomInUnitDisk() const {
            Vec3 p;
            do {
                p = 2.0 * Vec3(drand48(), drand48(),0 ) - Vec3(1, 1, 0);
            } while (dot(p, p) >= 1.0);
            return p;
        }
};

#endif /* _PERSPECTIVE_CAMERA_H_ */

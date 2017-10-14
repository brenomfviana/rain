#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "ray.h"
#include "vec3.h"

using namespace utils;

/*!
 * This class respresents a camera.
 */
class Camera {

    public:
		// The camera's origin
	    Point3 origin;

        /*!
         * Camera constructor.
         *
         * @param origin The camera's origin
         */
        Camera(Point3 origin = Point3()) {
            this->origin = origin;
        }

        /*!
         * Camera destructor.
         */
        ~Camera() {
            /* empty */
        }

        /*!
         * Get ray that reaches the point (u, v) in the view plane.
         *
         * @param u View plane x-axis point
         * @param v View plane y-axis point
         */
        virtual Ray get_ray(Vec3::RealType u, Vec3::RealType v) const = 0;
};

#include "parallel_camera.h"
#include "perspective_camera.h"

#endif /* _CAMERA_H_ */

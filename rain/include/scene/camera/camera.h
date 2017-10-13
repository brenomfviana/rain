#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "vec3.h"
#include "render/ray.h"

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
        Camera(Point3 origin = Point3(0, 0, 0)) :
            origin(origin) { /* empty */ }

        /*!
         * Get ray that reaches the point (u, v) in the view plane.
         *
         * @param u View plane x-axis point
         * @param v View plane y-axis point
         */
        virtual Ray getRay(Vec3::RealType u, Vec3::RealType v) const = 0;
};

#include "parallel_camera.h"
#include "perspective_camera.h"

#endif /* _CAMERA_H_ */

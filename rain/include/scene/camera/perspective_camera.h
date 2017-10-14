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
        Vec3 u;
        Vec3 v;
        Vec3 w;
        //
        Vec3::RealType lens_radius;

        /*!
         * Perspective camera constructor.
         *
         * @param origin The camera's origin
         * @param vfov The vertical field of view
         * @param aspect_ratio Aspect ratio
         * @param fd The focal distance of the view plane
         */
        PerspectiveCamera(Point3 look_from, Point3 look_at, Vec3 vup,
            Vec3::RealType vfov, Vec3::RealType aspect_ratio, Vec3::RealType aperture,
            Vec3::RealType fd);

        /*!
         * Perspective camera destructor.
         */
        ~PerspectiveCamera();

        Ray get_ray(Vec3::RealType u, Vec3::RealType v) const;

    private:
        Vec3 random_in_unit_disk() const;
};

#endif /* _PERSPECTIVE_CAMERA_H_ */

#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "utils/vec3.h"

using namespace utils;

/*!
 * This class respresents a camera.
 */
class Camera {

    public:
		// Lower left corner of the view plane
		Point3 llc;
		// Horizontal dimension of the view plane
	    Vec3 horizontal;
		// Vertical dimension of the view plane
	    Vec3 vertical;
		// The camera's origin
	    Point3 origin;

        /*!
         * Camera constructor.
         */
        Camera(Point3 llc_ = Point3(-8, -4.5, -4.5), Vec3 horizontal_ = Vec3(16, 0, 0),
                Vec3 vertical_ = Vec3(0, 9, 0), Point3 origin_ = Point3(0, 0, 0)) :
            llc(llc_), horizontal(horizontal_), vertical(vertical_), origin(origin_)
            { /* empty */ }
};

#endif /* _CAMERA_H_ */

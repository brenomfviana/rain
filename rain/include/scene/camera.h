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
         *
         * @param llc Lower left corner of the view plane
         * @param horizontal Horizontal dimension of the view plane
         * @param vertical Vertical dimension of the view plane
         * @param origin The camera's origin
         */
        Camera(Point3 llc = Point3(-8, -4.5, -4.5), Vec3 horizontal = Vec3(16, 0, 0),
                Vec3 vertical = Vec3(0, 9, 0), Point3 origin = Point3(0, 0, 0)) :
            llc(llc), horizontal(horizontal), vertical(vertical), origin(origin)
            { /* empty */ }
};

#endif /* _CAMERA_H_ */

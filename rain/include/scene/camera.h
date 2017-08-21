#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "utils/vec3.h"

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
        Camera(Point3 llc_, Vec3 horizontal_, Vec3 vertical_, Point3 origin_) :
            llc(llc_), horizontal(horizontal_), vertical(vertical_), origin(origin_)
            { /* empty */ }
};

#endif

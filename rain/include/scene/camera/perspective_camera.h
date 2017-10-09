#ifndef _PERSPECTIVE_CAMERA_H_
#define _PERSPECTIVE_CAMERA_H_

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

        /*!
         * Camera constructor.
         */
        PerspectiveCamera(float vfov, float aspectRatio, float dt) :
            { /* empty */ }
};

#endif /* _PERSPECTIVE_CAMERA_H_ */

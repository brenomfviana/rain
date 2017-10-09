#ifndef _ORTHOGONAL_CAMERA_H_
#define _ORTHOGONAL_CAMERA_H_

using namespace utils;

/*!
 * This class respresents a perspective camera.
 */
class OrthogonalCamera : public Camera {

    public:
        //
        Vec3 u;
        //
        Vec3 v;
        //
        Vec3 w;

        /*!
         * Camera constructor.
         */
        OrthogonalCamera(Vec3 lookAt, Vec3 lookFrom, Vec3 vup) {
            Vec3 gaze = lookAt - lookFrom;
            w = unitVector(gaze);
            v = cross(up, gaze);
            u = cross(xup, v);
        }
};

#endif /* _ORTHOGONAL_CAMERA_H_ */

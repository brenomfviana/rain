#ifndef _HIT_RECORD_H_
#define _HIT_RECORD_H_

#include "utils/vec3.h"

using namespace utils;

class Material;

/*!
 * Hit record of a point reached.
 */
class HitRecord {

    public:
        // Distance of the point reached
        float t;
        // Normal vector of the point reached
        Vec3 normal;
        // Shape origin
        Vec3 origin;
        // Shape material
        Material* material;
};

#endif /* _CAMERA_H_ */

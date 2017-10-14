#ifndef _HIT_RECORD_H_
#define _HIT_RECORD_H_

#include "vec3.h"

using namespace utils;

class Material;

/*!
 * Hit record of a point reached.
 */
class HitRecord {

    public:
        // Distance of the point reached
        Vec3::RealType t;
        // Normal vector of the point reached
        Vec3 normal;
        // Point of the shape reached
        Vec3 point;
        // Shape material
        Material* material;
};

#endif /* _HIT_RECORD_H_ */

#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "utils/vec3.h"

/*!
 * This class represents a shape material.
 */
class Material {

    public:
        // Albedo
        Vec3 kd;

        /*!
         * Material constructor.
         *
         * @param kd
         */
        Material(Vec3 kd_) : kd(kd_) { /* empty */ }
};

#endif

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
        // 
        Vec3 ks;
        // 
        float p;
        // 
        Vec3 ka;

        /*!
         * Material constructor.
         */
        Material() {}

        /*!
         * Material constructor.
         *
         * @param kd
         */
        Material(Vec3 kd_, Vec3 ks_, Vec3 ka_, float p_) : kd(kd_), ks(ks_), ka(ka_), p(p_)  { /* empty */ }
};

#endif

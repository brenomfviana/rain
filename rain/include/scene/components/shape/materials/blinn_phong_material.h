#ifndef _BLINN_PHONG_MATERIAL_H_
#define _BLINN_PHONG_MATERIAL_H_

#include <typeinfo>
#include "material.h"

using namespace utils;

/*!
 * This class respresents the Blinn-Phong material.
 */
class BlinnPhongMaterial : public Material {

    public:
        // Ambient coefficient
        Vec3 ka;
        // Diffuse coefficient
        Vec3 kd;
        // Specular coefficient
        Vec3 ks;
        // Specular shininess control parameter
        Vec3::RealType p;

        /*!
         * Blinn-Phong Material constructor.
         *
         * @param ka_ Ambient coefficient
         * @param kd_ Diffuse coefficient
         * @param ks_ Specular coefficient
         * @param p_ Specular shininess control parameter
         */
        BlinnPhongMaterial(Vec3 ka, Vec3 kd, Vec3 ks, Vec3::RealType p);

        /*!
         * Blinn-Phong Material destructor.
         */
        ~BlinnPhongMaterial();

        bool scatter(const Ray& r, const HitRecord& hr, RGB& attenuation,
            Ray& sray) const;
};

#endif /* _BLINN_PHONG_MATERIAL_H_ */

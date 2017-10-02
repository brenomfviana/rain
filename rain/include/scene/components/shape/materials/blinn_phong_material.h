#ifndef _BLINN_PHONG_MATERIAL_H_
#define _BLINN_PHONG_MATERIAL_H_

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
        float p;

        /*!
         * BlinnPhongMaterial constructor.
         *
         * @param ka_ Ambient coefficient
         * @param kd_ Diffuse coefficient
         * @param ks_ Specular coefficient
         * @param p_ Specular shininess control parameter
         */
        BlinnPhongMaterial(Vec3 ka_, Vec3 kd_, Vec3 ks_, float p_) :
            ka(ka_), kd(kd_), ks(ks_), p(p_)  { /* empty */ }

        bool scatter(const Ray& r, const HitRecord& hr, RGB& attenuation,
                Ray& sray) const {
            (void) (hr);
            sray = r;
            // No attenuation
            attenuation = Vec3(1, 1, 1);
            return true;
        }
};

#endif /* _BLINN_PHONG_MATERIAL_H_ */

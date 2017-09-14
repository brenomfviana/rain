#ifndef _BLINN_PHONG_MATERIAL_H_
#define _BLINN_PHONG_MATERIAL_H_

#include "material.h"

/*!
 * .
 */
class BlinnPhongMaterial : public Material {

    public:
        //
        Vec3 ka;
        // Albedo
        Vec3 kd;
        //
        Vec3 ks;
        //
        float p;

        /*!
         * BlinnPhongMaterial constructor.
         *
         * @param kd_
         * @param ks_
         * @param p_
         * @param ka_
         */
        BlinnPhongMaterial(Vec3 ka_, Vec3 kd_, Vec3 ks_, float p_) :
            ka(ka_), kd(kd_), ks(ks_), p(p_)  { /* empty */ }

        bool scatter(const Ray& incomingRay, const HitRecord& hitRecord,
            RGB& attenuation, Ray& scatteredRay) {
                //
                scatteredRay = incomingRay;
                // No attenuation
                attenuation = Vec3(1, 1, 1);
                return true;
                std::cout << hitRecord.t; // Remove warning
            }
};

#endif

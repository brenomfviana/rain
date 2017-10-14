#ifndef _LAMBERTIAN_MATERIAL_H_
#define _LAMBERTIAN_MATERIAL_H_

#include "material.h"

using namespace utils;

/*!
 * This class represents the lambertian material.
 */
class LambertianMaterial : public Material {

    private:
        // Albedo
        Vec3 albedo;

        /*!
         * Get random direction of a scattered ray.
         *
         * @return Random direction of a scattered ray
         */
        Vec3 random_in_unit_sphere() const;

    public:
        /*!
         * Lambertian material constructor.
         *
         * @param albedo Albedo
         */
        LambertianMaterial(Vec3 albedo);

        /*!
         * Lambertian material destructor.
         */
        ~LambertianMaterial();

        bool scatter(const Ray& r, const HitRecord& hr, RGB& attenuation,
                Ray& sray) const;
};

#endif /* _LAMBERTIAN_MATERIAL_H_ */

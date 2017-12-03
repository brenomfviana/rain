#ifndef _METAL_MATERIAL_H_
#define _METAL_MATERIAL_H_

#include "material.h"

using namespace utils;

/*!
 * This class represents a metal material.
 */
class MetalMaterial : public Material {

    private:
        //
        RGB albedo;
        Vec3::RealType fuzz;

        /*!
         * Get random direction of a scattered ray.
         *
         * @return Random direction of a scattered ray
         */
        Vec3 random_in_unit_sphere() const;

    public:

        /*!
         * Metal material constructor.
         *
         * @param albedo Albedo
         * @param fuzz
         */
        MetalMaterial(RGB albedo, Vec3::RealType fuzz);

        /*!
         * Metal material destructor.
         */
        ~MetalMaterial();

        /*!
         * Get reflected ray direction.
         *
         * @param v Incoming ray direction
         * @param n Normal vector
         *
         * @return Reflected ray direction
         */
        Vec3 reflect(const Vec3& v, const Vec3& n) const;

        bool scatter(const Ray& r, const HitRecord& hr, RGB& attenuation,
                Ray& sray) const;
};

#endif /* _METAL_MATERIAL_H_ */

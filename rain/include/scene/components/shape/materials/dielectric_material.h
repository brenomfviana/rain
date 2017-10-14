#ifndef _DIELECTRIC_MATERIAL_H_
#define _DIELECTRIC_MATERIAL_H_

#include <cmath>
#include "material.h"

using namespace utils;

/*!
 * This class represents a metal material.
 */
class DielectricMaterial : public Material {

    private:
        //
        Vec3::RealType ri;

    public:
        /*!
         * Dielectric material constructor.
         *
         * @param ri
         */
        DielectricMaterial(Vec3::RealType ri);


        /*!
         * Dielectric material destructor.
         */
        ~DielectricMaterial();

        /*!
         * .
         */
        Vec3::RealType schlick(Vec3::RealType cosine, Vec3::RealType ri) const;

        /*!
         * Get refracted ray direction.
         *
         * @param v Incoming ray direction
         * @param n Normal vector
         *
         * @return If the ray was refracted
         */
        bool refract(const Vec3& v, const Vec3& n, Vec3::RealType ni_over_nt,
                Vec3& refracted) const;

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

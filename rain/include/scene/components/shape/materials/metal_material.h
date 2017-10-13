#ifndef _METAL_MATERIAL_H_
#define _METAL_MATERIAL_H_

#include "material.h"

using namespace utils;

/*!
 * This class represents a metal material.
 */
class MetalMaterial : public LambertianMaterial {

    public:
        //
        Vec3::RealType fuzz;

        /*!
         * Metal material constructor.
         *
         * @param albedo Albedo
         * @param fuzz
         */
        MetalMaterial(Vec3 albedo, Vec3::RealType fuzz) :
            LambertianMaterial(albedo), fuzz(fuzz) { /* empty */ }

        /*!
         * Get reflected ray direction.
         *
         * @param v Incoming ray direction
         * @param n Normal vector
         *
         * @return Reflected ray direction
         */
        Vec3 reflect(const Vec3& v, const Vec3& n) const {
			return v - 2 * dot(v, n) * n;
        }

        bool scatter(const Ray& r, const HitRecord& hr, RGB& attenuation,
                Ray& sray) const {
            Vec3 reflected = reflect(unitVector(r.getDirection()), hr.normal);
		    sray = Ray(hr.point, reflected + fuzz * randomInUnitSphere());
			attenuation = albedo;
			return (dot(sray.getDirection(), hr.normal) > 0);
        }
};

#endif /* _METAL_MATERIAL_H_ */

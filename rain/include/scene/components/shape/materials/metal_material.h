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
        float fuzz;

        /*!
         * .
         */
        MetalMaterial(Vec3 albedo_, int fuzz_) :
            LambertianMaterial(albedo_), fuzz(fuzz_) { /* empty */ }

        /*!
         * .
         */
        Vec3 reflect(const Vec3& v, const Vec3& n) const {
			return v - 2 * dot(v, n) * n;
        }

        bool scatter(const Ray& r, const HitRecord& hr, RGB& attenuation,
                Ray& sray) {
            Vec3 reflected = reflect(unitVector(r.getDirection()), hr.normal);
		    sray = Ray(hr.origin, reflected + fuzz * randomInUnitSphere());
			attenuation = albedo;
			return (dot(sray.getDirection(), hr.normal) > 0);
        }
};

#endif /* _METAL_MATERIAL_H_ */

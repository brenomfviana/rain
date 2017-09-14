#ifndef _METAL_MATERIAL_H_
#define _METAL_MATERIAL_H_

#include "material.h"

/*!
 * This class represents a shape material.
 */
class MetalMaterial : public LambertianMaterial {

    public:
        float fuzz;

        MetalMaterial(Vec3 albedo_, int fuzz_) :
            LambertianMaterial(albedo_), fuzz(fuzz_) { /* empty */ }

        Vec3 reflect(const Vec3& v, const Vec3& n) const {
			return v - 2 * dot(v, n) * n;
        }

        bool scatter(const Ray& incomingRay, const HitRecord& hr,
                     RGB& attenuation, Ray& scatteredRay) {
            Vec3 reflected = reflect(unitVector(incomingRay.getDirection()), hr.normal);
		    scatteredRay = Ray(hr.origin, reflected + fuzz * randomInUnitSphere());
			attenuation = albedo;
			return (dot(scatteredRay.getDirection(), hr.normal) > 0);
        }
};

#endif

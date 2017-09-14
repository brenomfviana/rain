#ifndef _LAMBERTIAN_MATERIAL_H_
#define _LAMBERTIAN_MATERIAL_H_

#include "material.h"

/*!
 * This class represents a shape material.
 */
class LambertianMaterial : public Material {

    public:
        Vec3 albedo;

        LambertianMaterial(Vec3 albedo_) : albedo(albedo_) { /* empty */ }

        Vec3 randomInUnitSphere() const {
			Vec3 p;
			do {
				p = 2.0 * Vec3(drand48(), drand48(), drand48()) - Vec3(1, 1, 1);
			} while (dot(p, p) >= 1.0);
			return p;
        }

        bool scatter(const Ray& incomingRay, const HitRecord& hr,
                     RGB& attenuation, Ray& scatteredRay) {
            (void) (incomingRay);
		    Vec3 target = hr.origin + hr.normal + randomInUnitSphere();
		    scatteredRay = Ray(hr.origin, target - hr.origin);
			attenuation = albedo;
			return true;
        }
};

#endif

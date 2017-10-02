#ifndef _LAMBERTIAN_MATERIAL_H_
#define _LAMBERTIAN_MATERIAL_H_

#include "material.h"

using namespace utils;

/*!
 * This class represents the lambertian material.
 */
class LambertianMaterial : public Material {

    public:
        // Albedo
        Vec3 albedo;

        /*!
         * Lambertian material constructor.
         *
         * @param albedo Albedo
         */
        LambertianMaterial(Vec3 albedo) : albedo(albedo) { /* empty */ }

        /*!
         * Get random direction of a scattered ray.
         *
         * @return Random direction of a scattered ray
         */
        Vec3 randomInUnitSphere() const {
			Vec3 p;
			do {
				p = 2.0 * Vec3(drand48(), drand48(), drand48()) - Vec3(1, 1, 1);
			} while (dot(p, p) >= 1.0);
			return p;
        }

        bool scatter(const Ray& r, const HitRecord& hr, RGB& attenuation,
                Ray& sray) const {
            (void) (r);
		    Vec3 target = hr.point + hr.normal + randomInUnitSphere();
		    sray = Ray(hr.point, target - hr.point);
			attenuation = albedo;
			return true;
        }
};

#endif /* _LAMBERTIAN_MATERIAL_H_ */

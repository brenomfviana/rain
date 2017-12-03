#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "vec3.h"
#include "ray.h"
#include "scene/components/hit_record.h"

using namespace utils;

/*!
 * This class represents a shape material.
 */
class Material {

    public:
        /*!
         * Scatter the incoming ray.
         *
         * @param incoming_ray The incoming ray.
         * @param hit_record The hit record information (normal, p, material, t
         * of ray).
         * @param attenuation The attenuation of the ray after reflection (for
         * each RGB channel).
         * @param scattered_ray The produced scattered ray.
         *
         * @return true if the there is any scattered ray and false otherwise.
         */
        virtual bool scatter(const Ray& incoming_ray, const HitRecord& hit_record,
            RGB& attenuation, Ray& scattered_ray) const = 0;

        virtual Vec3 emitted(Vec3::RealType u, Vec3::RealType v, const Vec3& p) const {
            (void) u;
            (void) v;
            (void) p;
            return Vec3(0, 0, 0);
        }
};

#include "blinn_phong_material.h"
#include "toon_material.h"
#include "lambertian_material.h"
#include "metal_material.h"
#include "dielectric_material.h"
#include "diffuse_light_material.h"

#endif /* _MATERIAL_H_ */

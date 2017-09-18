#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "render/ray.h"
#include "utils/vec3.h"
#include "scene/components/hit_record.h"

using namespace utils;

/*!
 * This class represents a shape material.
 */
class Material {

    public:
        /*!
         * .
         *
         * @param incomingRay The incoming ray.
         * @param hit_record The hit record information (normal, p, material, t
         * of ray).
         * @param attenuation The attenuation of the ray after reflection (for
         * each RGB channel).
         * @param scatteredRay The produced scattered ray.
         *
         * @return true if the there is any scattered ray and false otherwise.
         */
        virtual bool scatter(const Ray& incomingRay, const HitRecord& hitRecord,
            RGB& attenuation, Ray& scatteredRay) = 0;
};

#include "blinn_phong_material.h"
#include "lambertian_material.h"
#include "metal_material.h"
#include "dielectric_material.h"

#endif /* _MATERIAL_H_ */

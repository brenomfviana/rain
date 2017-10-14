#ifndef _SHADER_H_
#define _SHADER_H_

#include "ray.h"
#include "vec3.h"
#include "scene/scene.h"
#include "scene/components/hit_record.h"

using namespace utils;

/*!
 * This class respresents a shader.
 */
class Shader {

    public:
        /*!
         * Get pixel color.
         *
         * @param r Incoming ray
         * @param scene Scene
         * @param nrays Number of rays of the recursion
         *
         * @return Pixel color
         */
        virtual RGB color(const Ray& r, const Scene& scene, int nrays) const = 0;

    protected:
        /*!
         * Get background color. Calculates the background color gradient.
         *
         * @param r Incoming ray
         * @param scene Scene
         */
        RGB background(const Ray& r, const Scene& scene) const;

        /*!
         * Check if the ray hit something.
         *
         * @param r Incoming ray
         * @param scene Scene
         * @param hr Hit record
         */
        bool intersect(const Ray& r, const Scene& scene, const Vec3::RealType tMin,
            const Vec3::RealType tMax, HitRecord& hr) const;
};

#include "background_shader.h"
#include "normals2rgb_shader.h"
#include "depth_map_shader.h"
#include "blinn_phong_shader.h"
#include "toon_shader.h"
#include "lambertian_shader.h"

#endif /* _SHADER_H_ */

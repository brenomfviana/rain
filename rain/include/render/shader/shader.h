#ifndef _SHADER_H_
#define _SHADER_H_

#include "utils/vec3.h"
#include "scene/scene.h"
#include "render/ray.h"
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
        inline RGB background(const Ray& r, const Scene& scene) const {
            // Get background corners colors
            RGB ul = scene.background.upperLeft;
            RGB ll = scene.background.lowerLeft;
            RGB ur = scene.background.upperRight;
            RGB lr = scene.background.lowerRight;
            // Bilinear interpolation
            auto rd = r.getDirection();
            auto x = (rd.x() * 0.25) + 0.5;
            auto y = (rd.y() * 0.5) + 0.5;
            return (1 - y) * ((1 - x) * ll + x * lr) +
                        y  * ((1 - x) * ul + x * ur);
        }

        /*!
         * Check if the ray hit something.
         *
         * @param r Incoming ray
         * @param scene Scene
         * @param hr Hit record
         */
        bool intersect(const Ray& r, const Scene& scene, float tMin, float tMax,
                HitRecord& hr) const {
            hr.t = std::numeric_limits<float>::infinity();
            // Check if hit scene components
            for (auto &shape : scene.components) {
                HitRecord haux;
                if (shape->hit(r, tMin, tMax, haux)) {
                    // Check which object is in front
                    if (haux.t > -1 && hr.t > haux.t) {
                        hr.t = haux.t;
                        hr.point = haux.point;
                        hr.normal = haux.normal;
                        hr.material = haux.material;
                    }
                }
            }
            return (hr.t > 0 && hr.t < std::numeric_limits<float>::infinity());
        }
};

#include "background_shader.h"
#include "normals2rgb_shader.h"
#include "depth_map_shader.h"
#include "blinn_phong_shader.h"
#include "cel_shader.h"
#include "lambertian_shader.h"

#endif /* _SHADER_H_ */

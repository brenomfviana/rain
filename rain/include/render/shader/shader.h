#ifndef _SHADER_H_
#define _SHADER_H_

#include "utils/vec3.h"
#include "scene/scene.h"
#include "render/ray.h"
#include "scene/components/hit_record.h"

/*!
 * This class respresents a shader.
 */
class Shader {

    public:
        /*!
         * .
         */
        virtual RGB color(const Ray& r, Scene& scene, int nrays) const = 0;

    protected:
        /*!
         * .
         */
        bool intersect(const Ray& r, Scene& scene, HitRecord& hr) const {
            // Check hit
            float tMin = 0;
            float tMax = 10;
            //
            hr.t = std::numeric_limits<float>::infinity();
            //
            for (auto &shape : scene.components) {
                //
                HitRecord haux;
                //
                if (shape->hit(r, tMin, tMax, haux)) {
                    //
                    if (haux.t > -1 && hr.t > haux.t) {
                        hr.t = haux.t;
                        hr.origin = haux.origin;
                        hr.normal = haux.normal;
                        hr.material = haux.material;
                    }
                }
            }
            return (hr.t > 0 && hr.t < std::numeric_limits<float>::infinity());
        }
};

#include "normal.h"
#include "lambertian.h"
#include "depth_map.h"
#include "blinn_phong.h"

#endif

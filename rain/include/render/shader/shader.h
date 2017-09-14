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
        virtual RGB color(const Ray& r, const Scene& scene, int nrays) const = 0;

    protected:
        /*!
         * .
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
            return (1 - y) * ((1 - x) * ll + x * lr) + y * ((1 - x) * ul + x * ur);
            // return ((ll * (1 - y) + ul * y * (1 - x)) + (lr * (1 - y) * x) + (ur * y * x));
        }


        /*!
         * .
         */
        bool intersect(const Ray& r, const Scene& scene, HitRecord& hr) const {
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

#include "background.h"
#include "normals2rgb.h"
#include "depth_map.h"
#include "blinn_phong.h"
#include "lambertian.h"

#endif

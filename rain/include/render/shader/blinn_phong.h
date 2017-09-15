#ifndef _BLINN_PHONG_SHADER_H_
#define _BLINN_PHONG_SHADER_H_

#include <cmath>
#include <algorithm>
#include "shader.h"
#include "utils/vec3.h"
#include "scene/components/light.h"

/*!
 * .
 */
class BlinnPhongShader : public Shader {

    private:
        //
        RGB ambientLight;

    public:
        /*!
         * .
         */
        BlinnPhongShader(RGB ambientLight_) : ambientLight(ambientLight_)
            {/* empty */}

        /*!
         * .
         */
        RGB color(const Ray& r, const Scene& scene, int nrays) const {
            (void) nrays;
            // Check hit
            HitRecord hr;
            if (intersect(r, scene, hr)) {
                //
                BlinnPhongMaterial* material =
                    dynamic_cast<BlinnPhongMaterial*>(hr.material);
                //
                RGB c = material->ka * ambientLight;
                // Check shadows
                HitRecord shr;
                for (auto& light : scene.lights) {
                    if (!intersect(Ray(hr.origin, light->direction), scene, shr)) {
                        c += blinnPhong(r, light, hr);
                    }
                }
                // Fix specular
                c = RGB(std::min(1.f, float(c[RGB::R])),
                        std::min(1.f, float(c[RGB::G])),
                        std::min(1.f, float(c[RGB::B])));
                // Return resulting color
                return c;
            } else {
                return background(r, scene);
            }
        }

    private:
        /*!
         * .
         */
        RGB blinnPhong(const Ray& r, Light* light, HitRecord& hr) const {
            // L.N
            BlinnPhongMaterial* material = dynamic_cast<BlinnPhongMaterial*>(hr.material);
            Vec3 ln = unitVector(light->direction - r.getDirection());
            float lambertian = std::max(0.f, dot(ln, hr.normal));
            float specular = 0.0;
            // Blinn Phong
            Vec3 H = unitVector(ln + unitVector(-r.getDirection()));
            // N.H
            specular = std::max(0.f, dot(hr.normal, H));
            specular = std::pow(specular, material->p);
            //
            return material->kd * lambertian * light->intensity +
                   material->ks * specular * light->intensity;
        }
};

#endif

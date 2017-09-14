#ifndef _LAMBERTIAN_SHADER_H_
#define _LAMBERTIAN_SHADER_H_

#include "shader.h"
#include "scene/components/shape/materials/material.h"

/*!
 * This class respresents a normal shader.
 */
class LambertianShader : public Shader {

    public:
        /*!
         * .
         */
        RGB color(const Ray& r, const Scene& scene, int nrays) const {
            if (nrays-- == 0) {
                return RGB(1, 1, 1);
            } else {
                // Check hit
                HitRecord hr;
                if (intersect(r, scene, hr)) {
                    //
                    LambertianMaterial* m =
                        dynamic_cast<LambertianMaterial*>(hr.material);
                    Ray scatteredRay;
                    RGB attenuation;
                    RGB c;
                    //
                    for (auto &light : scene.lights) {
                        c += lights(r, light, hr);
                    }
                    //
                    if (m->scatter(r, hr, attenuation, scatteredRay)) {
                        c *= 0.5 * attenuation * color(scatteredRay, scene, nrays);
                        return c;
                    }
                    return RGB(1, 1, 1);
                } else {
                    return background(r, scene);
                }
            }
        }

    private:
        /*!
         * .
         */
        RGB lights(const Ray& r, Light* light, HitRecord& hr) const {
            // L.N
            LambertianMaterial* material = dynamic_cast<LambertianMaterial*>(hr.material);
            Vec3 ln = unitVector(light->direction - r.getDirection());
            float lambertian = std::max(0.f, dot(ln, hr.normal));
            //
            return material->albedo * lambertian * light->intensity;
        }
};

#endif

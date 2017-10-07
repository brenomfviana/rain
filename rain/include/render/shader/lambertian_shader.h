#ifndef _LAMBERTIAN_SHADER_H_
#define _LAMBERTIAN_SHADER_H_

#include "shader.h"
#include "scene/components/shape/materials/material.h"

using namespace utils;

/*!
 * This class respresents the Lambertian shader.
 */
class LambertianShader : public Shader {

    public:
        RGB color(const Ray& r, const Scene& scene, int nrays) const {
            // Check if recursion is over
            if (nrays-- == 0) {
                return RGB(1, 1, 1);
            } else {
                // Check hit
                HitRecord hr;
                if (intersect(r, scene, 0, 10, hr)) {
                    RGB c;
                    /*HitRecord shr;
                    for (auto &light : scene.lights) {
                        c += lights(r, light, hr);
                    }*/
                    //
                    Ray scatteredRay;
                    RGB attenuation;
                    // Shape material
                    Material* m = hr.material;
                    // Check if the ray will be scattered
                    if (m->scatter(r, hr, attenuation, scatteredRay)) {
                        // Get the color from where the scattered ray reaches
                        c = 0.5 * attenuation * color(scatteredRay, scene, nrays);
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
        RGB lights(const Ray& r, Light* light, HitRecord& hr) const {
            // L.N
            Vec3 ln = unitVector(light->direction - r.getDirection());
            float lambertian = std::max(0.f, dot(ln, hr.normal));
            //
            if (typeid(*hr.material) == typeid(LambertianMaterial)) {
                LambertianMaterial* material = dynamic_cast<LambertianMaterial*>(hr.material);
                //
                return material->albedo * lambertian * light->intensity;
            } else if (typeid(*hr.material) == typeid(MetalMaterial)) {
                MetalMaterial* material = dynamic_cast<MetalMaterial*>(hr.material);
                //
                return material->albedo * lambertian * light->intensity;
            } else {
                throw "Unkown material.";
            }
        }
        */
};

#endif /* _LAMBERTIAN_SHADER_H_ */

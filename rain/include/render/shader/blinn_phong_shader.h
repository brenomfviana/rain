#ifndef _BLINN_PHONG_SHADER_H_
#define _BLINN_PHONG_SHADER_H_

#include <cmath>
#include <algorithm>
#include "shader.h"
#include "scene/components/light/light.h"

using namespace utils;

/*!
 * This class represents the Blinn-Phong shader.
 */
class BlinnPhongShader : public Shader {

    private:
        // Ambient light
        RGB alight;

    public:
        /*!
         * Blinn-Phong shader constructor.
         *
         * @param alight_ Ambient light
         */
        BlinnPhongShader(RGB alight_) : alight(alight_)
            { /* empty */ }

        RGB color(const Ray& r, const Scene& scene, int nrays) const {
            (void) nrays;
            // Check hit
            HitRecord hr;
            if (intersect(r, scene, 0, 10, hr)) {
                // Get Blinn-Phong material
                BlinnPhongMaterial* material =
                    dynamic_cast<BlinnPhongMaterial*>(hr.material);
                // Ambient light on the shape
                RGB c = material->ka * alight;
                // Lighting
                HitRecord shr;
                float t = 10;
                for (auto& light : scene.lights) {
                    if (typeid(*light) == typeid(PointLight)) {
                        PointLight* l = dynamic_cast<PointLight*>(light);
                        t = (l->getOrigin() - hr.point).length();
                    } else if (typeid(*light) == typeid(Spotlight)) {
                        Spotlight* l = dynamic_cast<Spotlight*>(light);
                        t = (l->getOrigin() - hr.point).length();
                    }
                    // Check shadows
                    if (!intersect(Ray(hr.point, unitVector(light->getDirection(hr.point))),
                            scene, 0, t, shr)) {
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
         * Applies the Blinn-Phong shadding model.
         *
         * @param r Incoming ray
         * @param light Scene light
         * @param hr Hit record
         *
         * @return Corresponding color
         */
        RGB blinnPhong(const Ray& r, Light* light, HitRecord& hr) const {
            BlinnPhongMaterial* material =
                dynamic_cast<BlinnPhongMaterial*>(hr.material);
            // Lambertian
            float lambertian = std::max(0.f,
                dot(unitVector(light->getDirection(hr.point)), hr.normal));
            // Blinn-Phong
            Vec3 H = unitVector(unitVector(light->getDirection(hr.point))
                + unitVector(-r.getDirection()));
            // N.H
            float specular = std::max(0.f, dot(hr.normal, H));
            specular = std::pow(specular, material->p);
            //
            return material->kd * lambertian * light->getIntensity(hr.point) +
                   material->ks * specular * light->getIntensity(hr.point);
        }
};

#endif /* _BLINN_PHONG_SHADER_H_ */

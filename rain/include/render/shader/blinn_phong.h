#ifndef _BLINN_PHONG_SHADER_H_
#define _BLINN_PHONG_SHADER_H_

#include <cmath>
#include "shader.h"
#include "utils/vec3.h"
#include "scene/components/light.h"

/*!
 * .
 */
class BlinnPhongShader : public Shader {

    public:
        /*!
         * .
         */
        RGB color(const Ray& r, Scene& scene, int nrays) const {
            // Check hit
            HitRecord hr;
            if (intersect(r, scene, hr)) {
                RGB c;
                // RGB c = hr.material.ka * scene.alight.intensity;
                for (auto &light : scene.lights) {
                    c += blinnPhong(r, light, hr);
                }
                // Return resulting color
                return c;
            } else {
                // Get background corners colors
                RGB ul = scene.background.upperLeft;
                RGB ll = scene.background.lowerLeft;
                RGB ur = scene.background.upperRight;
                RGB lr = scene.background.lowerRight;
                // Bilinear interpolation
                auto rd = r.getDirection();
                auto w = (rd.x() * 0.25) + 0.5;
                auto x = (rd.y() * 0.5) + 0.5;
                return ((ll * (1 - x) * (1 - w)) + (ul * x * (1 - w)) +
                    (lr * (1 - x) * w) + (ur * x *w));
            }
        }

    private:
        /*!
         * .
         */
        RGB blinnPhong(const Ray& r, Light* light, HitRecord& hr) const {
            // L.N
            // std::cout << light->intensity << "\n";
            Vec3 ld = unitVector(light->direction - r.getDirection());
            float lambertian = std::max(0.f, dot(ld, hr.normal));
            float specular = 0.0;
            //
            if (lambertian > 0.0) {
                // Blinn Phong
                Vec3 H = unitVector(ld + unitVector(-r.getDirection()));
                // N.H
                specular = std::max(0.f, dot(hr.normal, H));
                specular = std::pow(specular, hr.material.p);
            }
            return hr.material.kd * lambertian * light->intensity +
                hr.material.ks * specular * light->intensity;
        }
};

#endif

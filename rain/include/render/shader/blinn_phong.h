#ifndef _BLINN_PHONG_SHADER_H_
#define _BLINN_PHONG_SHADER_H_

#include <cmath>
#include "shader.h"
#include "utils/vec3.h"

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
                Vec3 light(-8,2,0);
                Vec3 H = (light + r.getDirection()) / (light + r.getDirection()).length();
                float lambertian = std::max(0.0, dot(hr.normal, light));
                float specular = std::max(0.0, std::pow(dot(hr.normal, H), 64.f));
                return Vec3(1,1,1) * lambertian * hr.material.kd +
                        Vec3(1,1,1) * specular * hr.material.ks;
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
};

#endif

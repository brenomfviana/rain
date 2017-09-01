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
                Vec3 light1(-8,2,0);
                Vec3 light2(2,1,2);
                Vec3 ls[2] = {light1, light2};
                Vec3 i1(0.5,0.5,0);
                Vec3 i2(1,1,1);
                Vec3 is[2] = {i1, i2};
                //
                RGB c;
                for (int i = 0; i < 2; i++) {
                    c += d(ls[i], is[i], r, hr);
                }
                //
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
        //
        RGB d(Vec3 light, Vec3 i, const Ray& r, HitRecord& hr) const {
            light = unitVector(light);
            Vec3 H = unitVector(light + r.getDirection());
            float lambertian = std::max(0.f, dot(hr.normal, -light));
            float specular = std::max(0.f, dot(hr.normal, H));
            specular = std::pow(specular, hr.material.p);
            return i * lambertian * hr.material.kd +
                    i * specular * hr.material.ks;
        }
};

#endif

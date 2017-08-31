#ifndef _LAMBERTIAN_SHADER_H_
#define _LAMBERTIAN_SHADER_H_

#include "shader.h"

/*!
 * This class respresents a normal shader.
 */
class LambertianShader : public Shader {

    public:
        /*!
         * .
         */
        RGB color(const Ray& r, Scene& scene, int nrays) const {
            // Check hit
            HitRecord hr;
            if (intersect(r, scene, hr)) {
                return dot(-Vec3(-0.5, 0.5, -1), hr.normal) * RGB(0, 0, 0.95) * Vec3(1, 1, 1);
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

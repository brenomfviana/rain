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
                    LambertianMaterial* m = dynamic_cast<LambertianMaterial*>(hr.material);
                    Ray scatteredRay;
                    RGB attenuation;
                    //
                    if (m->scatter(r, hr, attenuation, scatteredRay)) {
                        RGB c = 0.5 * attenuation * color(scatteredRay, scene, nrays);
                        return c;
                    }
                    return RGB(1, 1, 1);
                } else {
                    return background(r, scene);
                }
            }
        }
};

#endif

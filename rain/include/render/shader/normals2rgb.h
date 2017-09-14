#ifndef _NORMALS_2_RGB_SHADER_H_
#define _NORMALS_2_RGB_SHADER_H_

#include "shader.h"

/*!
 * This class respresents a normal shader.
 */
class Normals2RGBShader : public Shader {

    public:
        /*!
         * .
         */
        RGB color(const Ray& r, const Scene& scene, int nrays) const {
            // Check hit
            HitRecord hr;
            if (intersect(r, scene, hr)) {
                return ((hr.normal + Vec3(1, 1, 1)) * 0.5);
            } else {
                return background(r, scene);
                nrays = nrays; // Remove warning
            }
        }
};

#endif

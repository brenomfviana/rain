#ifndef _NORMALS_2_RGB_SHADER_H_
#define _NORMALS_2_RGB_SHADER_H_

#include "shader.h"

/*!
 * This class respresents the normal shader.
 */
class Normals2RGBShader : public Shader {

    public:
        RGB color(const Ray& r, const Scene& scene, int nrays) const {
            (void) (nrays);
            // Check hit
            HitRecord hr;
            if (intersect(r, scene, 0, 10, hr)) {
                // Normal 2 RGB
                return ((hr.normal + Vec3(1, 1, 1)) * 0.5);
            } else {
                return background(r, scene);
            }
        }
};

#endif /* _NORMALS_2_RGB_SHADER_H_ */

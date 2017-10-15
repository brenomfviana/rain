#ifndef _NORMALS_2_RGB_SHADER_H_
#define _NORMALS_2_RGB_SHADER_H_

#include "shader.h"

/*!
 * This class respresents the normal to RGB shader.
 */
class Normals2RGBShader : public Shader {

    public:
        RGB color(const Ray& r, const Scene& scene, int nrays) const;
};

#endif /* _NORMALS_2_RGB_SHADER_H_ */

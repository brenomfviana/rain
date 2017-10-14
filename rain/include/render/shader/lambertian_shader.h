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
        RGB color(const Ray& r, const Scene& scene, int nrays) const;
};

#endif /* _LAMBERTIAN_SHADER_H_ */

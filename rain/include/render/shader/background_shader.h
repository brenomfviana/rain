#ifndef _BACKGROUND_SHADER_H_
#define _BACKGROUND_SHADER_H_

#include "shader.h"

using namespace utils;

/*!
 * This class respresents the backgroud shader.
 */
class BackgroundShader : public Shader {

    public:
        /*!
         * Background shader constructor.
         */
        BackgroundShader() { /* empty */ }

        RGB color(const Ray& r, const Scene& scene, int nrays) const {
            (void) (nrays);
            return background(r, scene);
        }
};

#endif /* _BACKGROUND_SHADER_H_ */

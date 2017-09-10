#ifndef _BACKGROUND_SHADER_H_
#define _BACKGROUND_SHADER_H_

#include "shader.h"
#include "utils/vec3.h"

/*!
 * This class respresents the backgroud shader.
 */
class BackgroundShader : public Shader {

    public:
        /*!
         * .
         */
        BackgroundShader() { /* empty */ }

        /*!
         * .
         */
        RGB color(const Ray& r, const Scene& scene, int nrays) const {
            return background(r, scene);
            nrays = nrays; // Remove warning
        }
};

#endif

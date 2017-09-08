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
        RGB color(const Ray& r, Scene& scene, int nrays) const {
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
            nrays = nrays; // Remove warning
        }
};

#endif

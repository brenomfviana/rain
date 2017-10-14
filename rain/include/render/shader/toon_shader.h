#ifndef _TOON_SHADER_H_
#define _TOON_SHADER_H_

#include "shader.h"
#include "scene/components/light/light.h"

using namespace utils;

/*!
 * This class represents the Blinn-Phong shader.
 */
class ToonShader : public Shader {

    private:
        // Border color
        RGB border_color;

    public:
        /*!
         * Toon shader constructor.
         *
         * @param border_color Border color
         */
        ToonShader(RGB border_color);

        /*!
         * Toon shader destructor.
         */
        ~ToonShader();

        RGB color(const Ray& r, const Scene& scene, int nrays) const;
};

#endif /* _TOON_SHADER_H_ */

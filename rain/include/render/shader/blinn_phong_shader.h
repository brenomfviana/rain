#ifndef _BLINN_PHONG_SHADER_H_
#define _BLINN_PHONG_SHADER_H_

#include <cmath>
#include <algorithm>
#include "shader.h"
#include "scene/components/light/light.h"

using namespace utils;

/*!
 * This class represents the Blinn-Phong shader.
 */
class BlinnPhongShader : public Shader {

    private:
        // Ambient light
        RGB alight;

        /*!
         * Applies the Blinn-Phong shadding model.
         *
         * @param r Incoming ray
         * @param light Scene light
         * @param hr Hit record
         *
         * @return Corresponding color
         */
        RGB blinnPhong(const Ray& r, const Light* light, HitRecord& hr) const;

    public:
        /*!
         * Blinn-Phong shader constructor.
         *
         * @param alight Ambient light
         */
        BlinnPhongShader(RGB alight);

        /*!
         * Blinn-Phong shader destructor.
         */
        ~BlinnPhongShader();

        RGB color(const Ray& r, const Scene& scene, int nrays) const;
};

#endif /* _BLINN_PHONG_SHADER_H_ */

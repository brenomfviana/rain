#ifndef _CEL_MATERIAL_H_
#define _CEL_MATERIAL_H_

#include <vector>
#include "material.h"

/*!
 * This class respresents the cel material (toon material).
 */
class CelMaterial : public Material {

	public:
        // Material colors
        std::vector<RGB> colors;
        // Angle ranges at which each color appears
        std::vector<float>angles;

        /*!
         * Cel material constructor.
         *
         * @param colors Material colors.
         * @param angles Angle ranges at which each color appears.
         */
		CelMaterial(std::vector<RGB> colors, std::vector<float> angles) :
                colors(colors), angles(angles)
            { /* empty */ }

        bool scatter (const Ray& r, const HitRecord& hr, RGB& attenuation,
                Ray& sray) const {
            (void) (hr);
            sray = r;
            // No attenuation
            attenuation = Vec3(1, 1, 1);
            return true;
        }
};

#endif

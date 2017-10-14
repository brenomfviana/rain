#ifndef _TOON_MATERIAL_H_
#define _TOON_MATERIAL_H_

#include <vector>
#include "material.h"

/*!
 * This class respresents the toon material.
 */
class ToonMaterial : public Material {

	public:
        // Material colors
        std::vector<RGB> colors;
        // Angle ranges at which each color appears
        std::vector<Vec3::RealType>angles;

        /*!
         * Toon material constructor.
         *
         * @param colors Material colors.
         * @param angles Angle ranges at which each color appears.
         */
		ToonMaterial(std::vector<RGB> colors, std::vector<Vec3::RealType> angles);

		/*!
         * Toon material destructor.
         */
		~ToonMaterial();

        bool scatter(const Ray& r, const HitRecord& hr, RGB& attenuation,
                Ray& sray) const;
};

#endif /* _TOON_MATERIAL_H_ */

#ifndef _DIRECTIONAL_LIGHT_H_
#define _DIRECTIONAL_LIGHT_H_

#include "scene/components/light/light.h"

using namespace utils;

/*!
 * This class represents a directional light.
 */
class DirectionalLight : public Light {

    protected:
        Vec3 direction;

    public:
        /*!
         * Directional light constructor.
         *
         * @param direction Light direction
         * @param intensity Light intensity
         */
        DirectionalLight(Vec3 direction = Vec3(1, 1, 1), Vec3 intensity = Vec3(1, 1, 1));

        /*!
         * Directional light destructor.
         */
        ~DirectionalLight();

        /*!
		 * Get directional light direction.
		 *
		 * @return Directional light direction
		 */
		Vec3 get_direction(Point3 p) const;

        /*!
         * Get directional light intensity.
         *
         * @return Directional light intensity
         */
        Vec3 get_intensity(Point3 p) const;
};

#endif /* _DIRECTIONAL_LIGHT_H_ */

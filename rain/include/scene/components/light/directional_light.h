#ifndef _DIRECTIONAL_LIGHT_H_
#define _DIRECTIONAL_LIGHT_H_

#include "scene/components/light/light.h"

using namespace utils;

/*!
 * This class represents a directional light.
 */
class DirectionalLight : public Light {

    protected:
        // Direction
        Vec3 direction;
        // Intensity
        Vec3 intensity;

    public:
        /*!
         * Light constructor.
         *
         * @param direction Light direction
         * @param intensity Light intensity
         */
        DirectionalLight(Vec3 direction = Vec3(1, 1, 1),
                Vec3 intensity = Vec3(1, 1, 1)) : Light(direction, intensity)
            { /* empty */ }

        /*!
		 * Get light direction.
		 *
		 * @return Light direction
		 */
		inline Vec3 getDirection() const { return direction; }

        /*!
         * Get light intensity.
         *
         * @return Light intensity
         */
        inline Vec3 getIntensity() const { return intensity; }
};

#endif /* _DIRECTIONAL_LIGHT_H_ */

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
        DirectionalLight(Vec3 direction = Vec3(1, 1, 1),
                         Vec3 intensity = Vec3(1, 1, 1))
        : Light(intensity), direction(direction) { /* empty */ }

        /*!
		 * Get directional light direction.
		 *
		 * @return Directional light direction
		 */
		inline Vec3 getDirection(Point3 p) const {
            (void) p;
            return direction;
        }

        /*!
         * Get directional light intensity.
         *
         * @return Directional light intensity
         */
        inline Vec3 getIntensity(Point3 p) const {
            (void) p;
            return intensity;
        }
};

#endif /* _DIRECTIONAL_LIGHT_H_ */

#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "utils/vec3.h"

using namespace utils;

/*!
 * This class represents a light.
 */
class Light {

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
        Light(Vec3 direction = Vec3(1, 1, 1), Vec3 intensity = Vec3(1, 1, 1)) :
            direction(direction), intensity(intensity) { /* empty */ }

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
        inline Vec3 getIntensity(Point3 p) const {
            (void) p;
            return intensity;
        }
};

typedef Light DirectionalLight;

#include "spotlight.h"

#endif /* _LIGHT_H_ */

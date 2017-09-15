#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "utils/vec3.h"

using namespace utils;

/*!
 * This class represents a light.
 */
class Light {

    private:
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
        Light(Vec3 direction_ = Vec3(1, 1, 1), Vec3 intensity_ = Vec3(1, 1, 1)) :
            direction(direction_), intensity(intensity_) { /* empty */ }

        /*!
		 * Get light direction.
		 *
		 * @return Light direction
		 */
		inline Vec3 getDirection(void) const { return direction; }

        /*!
         * Get light intensity.
         *
         * @return Light intensity
         */
        inline Vec3 getIntensity(void) const { return intensity; }
};

#endif /* _LIGHT_H_ */

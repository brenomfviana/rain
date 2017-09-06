#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "utils/vec3.h"

/*!
 * This class represents a light.
 */
class Light {

    public:
        // Direction
        Vec3 direction;
        // Intensity
        Vec3 intensity;

        Light() { /* empty */ }

        /*!
         * Light constructor.
         *
         * @param direction Light direction
         * @param intensity Light intensity
         */
        Light(Vec3 direction_, Vec3 intensity_) : direction(direction_),
            intensity(intensity_) { /* empty */ }
};

#endif

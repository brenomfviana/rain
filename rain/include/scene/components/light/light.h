#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "utils/vec3.h"

using namespace utils;

/*!
 * This class represents a light.
 */
class Light {

    protected:
        // Intensity
        Vec3 intensity;

    public:
        /*!
         * Light constructor.
         *
         * @param intensity Light intensity
         */
        Light(Vec3 intensity = Vec3(1, 1, 1)) : intensity(intensity)
            { /* empty */ }

        /*!
		 * Get light direction.
		 *
		 * @return Light direction
		 */
		virtual Vec3 getDirection(Point3 p) const = 0;

        /*!
         * Get light intensity.
         *
         * @return Light intensity
         */
        virtual Vec3 getIntensity(Point3 p) const = 0;
};

#include "directional_light.h"
#include "point_light.h"
#include "spotlight.h"

#endif /* _LIGHT_H_ */

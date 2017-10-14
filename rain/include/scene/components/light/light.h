#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "vec3.h"

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
        Light(Vec3 intensity = Vec3(1, 1, 1)) {
            this->intensity = intensity;
        }

        /*!
         * Light destructor.
         */
        ~Light() {
            /* empty */
        }

        /*!
		 * Get light direction.
		 *
		 * @return Light direction
		 */
		virtual Vec3 get_direction(Point3 p) const = 0;

        /*!
         * Get light intensity.
         *
         * @return Light intensity
         */
        virtual Vec3 get_intensity(Point3 p) const = 0;
};

#include "directional_light.h"
#include "point_light.h"

#endif /* _LIGHT_H_ */

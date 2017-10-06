#ifndef _POINT_LIGHT_H_
#define _POINT_LIGHT_H_

#include "utils/vec3.h"

using namespace utils;

/*!
 * This class represents a light.
 */
class PointLight : public Light {

    protected:
        // Light origin
        Point3 origin;

    public:
        /*!
         * Point light constructor.
         *
         * @param direction Light direction
         * @param intensity Light intensity
         */
        PointLight(Vec3 origin, Vec3 intensity = Vec3(1, 1, 1))
        : Light(Point3(0, 0, 0), intensity), origin(origin) { /* empty */ }

        /*!
		 * Get directional light direction.
		 *
		 * @return Directional light direction
		 */
		inline Vec3 getDirection(Point3 p) const {
            return p - origin;
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

#endif /* _POINT_LIGHT_H_ */

#ifndef _SPOTLIGHT_H_
#define _SPOTLIGHT_H_

#include <cmath>
#include "point_light.h"

using namespace utils;

/*!
 * This class represents a spotlight.
 */
class Spotlight : public PointLight {

    protected:
        // Spotlight direction
        Vec3 direction;
        // Spotlight angle
        float beam_angle;

    public:
        /*!
         * Spotlight constructor.
         *
         * @param origin Light origin
         * @param direction Light direction
         * @param intensity Light intensity
         */
        Spotlight(Point3 origin = Point3(0, 0, 0), Vec3 direction = Vec3(1, 1, 1),
                Vec3 intensity = Vec3(1, 1, 1), float beam_angle = 90);

        /*!
         * Spotlight destructor.
         */
        ~Spotlight();

        /*!
		 * Get spotlight direction.
		 *
		 * @return Spotlight direction
		 */
		Vec3 get_direction(Point3 p) const;

        /*!
		 * Get spotlight intensity.
		 *
		 * @return Spotlight intensity
		 */
		Vec3 get_intensity(Point3 p) const;
};

#endif /* _SPOTLIGHT_H_ */

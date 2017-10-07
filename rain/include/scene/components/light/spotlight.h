#ifndef _SPOTLIGHT_H_
#define _SPOTLIGHT_H_

#include <cmath>
#include "scene/components/light/light.h"

using namespace utils;

/*!
 * This class represents a spotlight.
 */
class Spotlight : public PointLight {

    private:
        //
        Vec3 direction;
        // Angle
        float beamAngle;

    public:
        /*!
         * Light constructor.
         *
         * @param origin Light origin
         * @param direction Light direction
         * @param intensity Light intensity
         */
        Spotlight(Point3 origin = Point3(0, 0, 0), Vec3 direction = Vec3(1, 1, 1),
                Vec3 intensity = Vec3(1, 1, 1), float beamAngle = 90) :
            PointLight(origin, intensity), direction(direction), beamAngle(beamAngle)
            { /* empty */ }

        /*!
		 * Get light direction.
		 *
		 * @return Light direction
		 */
		inline Vec3 getDirection(Point3 p) const {
            Vec3 dir = origin - p;
            float angle = dot(-direction, dir) / ((-direction).length() * dir.length());
            if (angle >= beamAngle) {
                return dir;
            }
            return Vec3(0, 0, 0);
        }

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

#endif /* _SPOTLIGHT_H_ */

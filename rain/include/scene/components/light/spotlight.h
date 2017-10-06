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
        // Angle
        float beamAngle;
        //
        float fallOffAngle;

    public:
        /*!
         * Light constructor.
         *
         * @param origin Light origin
         * @param direction Light direction
         * @param intensity Light intensity
         */
        Spotlight(Point3 origin = Point3(0, 0, 0), float beamAngle = 90,
                float fallOffAngle = 180, Vec3 intensity = Vec3(1, 1, 1)) :
            PointLight(origin, intensity), beamAngle(beamAngle),
                fallOffAngle(fallOffAngle)
            { /* empty */ }

        /*!
		 * Get light direction.
		 *
		 * @return Light direction
		 */
		inline Vec3 getDirection(Point3 p) const {
            (void) p;
            return direction;
        }

        /*!
		 * Get light intensity.
		 *
		 * @return Light intensity
		 */
		inline Vec3 getIntensity(Point3 p) const {
            //
            Vec3 v = unitVector(p - origin);
            //
            float angle = std::acos(dot(v, this->getDirection(p)));
            //
            if (angle > beamAngle + fallOffAngle) {
                return RGB(0, 0, 0);
            } else if (angle > beamAngle) {
                float portion = 1 - ((angle - beamAngle) / fallOffAngle);
                return RGB(std::max(0.f, intensity[RGB::R] * portion),
                           std::max(0.f, intensity[RGB::G] * portion),
                           std::max(0.f, intensity[RGB::B] * portion));
            } else {
                return intensity;
            }
        }
};

#endif /* _SPOTLIGHT_H_ */

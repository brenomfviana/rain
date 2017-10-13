#ifndef _POINT_LIGHT_H_
#define _POINT_LIGHT_H_

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
         * @param intensity Light intensity
         */
        PointLight(Vec3 origin, Vec3 intensity = Vec3(1, 1, 1))
            : Light(intensity), origin(origin) { /* empty */ }

        /*!
		 * .
		 */
		inline Vec3 getOrigin() const {
            return origin;
        }

        /*!
		 * Get directional light direction.
		 *
		 * @return Directional light direction
		 */
		inline Vec3 getDirection(Point3 p) const {
            return origin - p;
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

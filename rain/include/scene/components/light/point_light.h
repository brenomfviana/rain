#ifndef _POINT_LIGHT_H_
#define _POINT_LIGHT_H_

#include "light.h"

using namespace utils;

/*!
 * This class represents a point light.
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
        PointLight(Point3 origin = Point3(), Vec3 intensity = Vec3(1, 1, 1));

        /*!
         * Point light destructor.
         */
        ~PointLight();

        /*!
		 * Get point light origin.
         *
         * @return Point light origin
		 */
		Vec3 get_origin() const;

        /*!
		 * Get point light direction.
		 *
		 * @return Point light direction
		 */
		Vec3 get_direction(Point3 p) const;

        /*!
         * Get point light intensity.
         *
         * @return Point light intensity
         */
        Vec3 get_intensity(Point3 p) const;
};

#include "spotlight.h"

#endif /* _POINT_LIGHT_H_ */

#ifndef _RAY_H_
#define _RAY_H_

#include "vec3.h"

using namespace utils;

/*!
 * This class represents a ray.
 */
class Ray {

	private:
		// Ray origin
		Point3 origin;
		// Ray direction
		Vec3 direction;

	public:
		typedef double RealType;

		/*!
		 * Ray constructor.
		 *
		 * @param origin Ray origin
		 * @param direction Ray direction
		 */
		Ray(const Point3 origin = Point3(), const Vec3 direction = Vec3()) {
			this->origin    = origin;
			this->direction = direction;
		}

		/*!
		 * Get ray origin.
		 *
		 * @return Ray origin
		 */
		inline Vec3 get_origin() const {
			return origin;
		}

		/*!
		 * Get ray direction.
		 *
		 * @return Ray direction
		 */
		inline Vec3 get_direction() const {
			return direction;
		}

		/*!
		 * Get the point to which the vector points.
		 *
		 * @param t Distance
		 *
		 * @return The point to which the vector points
		 */
		Point3 point_at(RealType t) const {
			return origin + (t * direction);
		}
};

#endif /* _RAY_H_ */

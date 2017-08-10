#ifndef _RAY_H_
#define _RAY_H_

#include "vec3.h"

using namespace utility;

class Ray {

	private:
		// Ray origin
		Point3 origin;
		// Ray direction
		Vec3 direction;

	public:
		// Alias
		typedef float RealType;

		/**
		 * Ray constructor.
		 *
		 * @param origin_ Ray origin
		 * @param direction_ Ray direction
		 */
		Ray(Point3 origin_ = Point3(), Vec3 direction_ = Vec3()) :
			origin(origin_), direction(direction_) { /* Empty */ }

		/* ------------------------ Access Methods -------------------------- */

		/**
		 * Get ray direction.
		 *
		 * @return Ray direction
		 */
		inline Vec3 getDirection(void) const { return direction; }

		/**
		 * Get ray origin.
		 *
		 * @return Ray origin
		 */
		inline Vec3 getOrigin(void) const { return origin; }

		/**
		 * TO COMMENT.
		 */
		Point3 pointAt(RealType t_) const {
			return origin + t_ * direction;
		}
};

#endif

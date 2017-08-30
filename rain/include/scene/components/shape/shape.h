#ifndef _SHAPE_H_
#define _SHAPE_H_

#include "utils/vec3.h"
#include "render/ray.h"
#include "scene/components/hit_record.h"

/*!
 * This class represents a shape.
 */
class Shape {

    protected:
        // Shape origin
        Vec3 origin;
        // Material

    public:
        /*!
         * Shape constructor.
         *
         * @param origin_ Shape origin
         */
        Shape(Vec3 origin_) : origin(origin_) { /* empty */ }

        /*!
         * Check if the ray has hit the shape. Returns true if the ray has hit
         * the shape and false otherwise.
         *
         * @param r Ray
         * @param tMin
         * @param tMax
         * @param hr Hit record
         *
         * @return True if the ray has hit the shape and false otherwise
         */
        virtual bool hit(Ray r, float tMin, float tMax, HitRecord& hr) = 0;
};

#endif

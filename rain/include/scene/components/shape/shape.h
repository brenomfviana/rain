#ifndef _SHAPE_H_
#define _SHAPE_H_

#include "utils/vec3.h"
#include "render/ray.h"
#include "materials/material.h"
#include "scene/components/hit_record.h"

using namespace utils;

/*!
 * This class represents a shape.
 */
class Shape {

    protected:
        // Shape origin
        Vec3 origin;
        // Shape material
        Material* material;

    public:

        /*!
         * Shape constructor.
         *
         * @param origin Shape origin
         * @param material Shape material
         */
        Shape(Vec3 origin, Material* material) :
            origin(origin), material(material)
                { /* empty */ }

        /*!
         * Shape constructor.
         *
         * @param origin Shape origin
         */
        Shape(Vec3 origin) : origin(origin) { /* empty */ }

        /*!
         * Get shape material.
         *
         * @return Shape material
         */
        inline Material* getMaterial() {
            return material;
        }

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

#endif /* _SHAPE_H_ */

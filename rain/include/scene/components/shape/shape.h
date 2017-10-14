#ifndef _SHAPE_H_
#define _SHAPE_H_

#include "vec3.h"
#include "ray.h"
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
         */
        Shape(Vec3 origin) {
            this->origin = origin;
        }

        /*!
         * Shape constructor.
         *
         * @param origin Shape origin
         * @param material Shape material
         */
        Shape(Vec3 origin, Material* material) {
            this->origin   = origin;
            this->material = material;
        }

        /*!
         * Shape destructor.
         */
        ~Shape() {
            /* empty */
        }

        /*!
         * Get shape material.
         *
         * @return Shape material
         */
        inline Material* get_material() {
            return this->material;
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
        virtual bool hit(Ray r, Vec3::RealType tMin, Vec3::RealType tMax, HitRecord& hr) = 0;
};

#include "sphere.h"

#endif /* _SHAPE_H_ */

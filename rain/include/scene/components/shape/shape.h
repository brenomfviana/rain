#ifndef _SHAPE_H_
#define _SHAPE_H_

#include "ray.h"
#include "vec3.h"
#include "transformation.h"
#include "materials/material.h"
#include "scene/components/hit_record.h"
#include <list>
#include <tuple>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace utils;

/*!
 * This class represents a shape.
 */
class Shape {

    protected:
        // Shape material
        Material* material;
        // Shape origin
        Vec3 origin;

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
         * @param t_min
         * @param t_max
         * @param hr Hit record
         *
         * @return True if the ray has hit the shape and false otherwise
         */
        virtual bool hit(Ray r, Vec3::RealType t_min, Vec3::RealType t_max, HitRecord& hr) = 0;

        /*!
         * .
         *
         * @param v .
         */
        virtual glm::mat4 translate(glm::vec3 v) = 0;

        /*!
         * .
         *
         * @param v .
         */
        virtual glm::mat4 rotate(glm::vec3 v) = 0;

        /*!
         * .
         *
         * @param v .
         */
        virtual glm::mat4 scale(glm::vec3 v) = 0;

        /*!
         * .
         *
         * @param ts .
         */
        virtual void transform(std::list<std::tuple<Transformation, Vec3>> ts) = 0;
};

#include "sphere.h"
#include "triangle.h"
#include "box.h"
#include "mesh.h"
#include "plane.h"

#endif /* _SHAPE_H_ */

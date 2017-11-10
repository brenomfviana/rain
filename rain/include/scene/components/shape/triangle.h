#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include "shape.h"

#define EPSILON 0.00000001

/*!
 * This class represents a sphere.
 */
class Triangle : public Shape {

    private:
        //
        Point3 v0;
        Point3 v1;
        Point3 v2;
        //
        bool back_facing_cull;

    public:

        /*!
         * Triangle constructor.
         */
        Triangle(Point3 v0, Point3 v1, Point3 v2, bool back_facing_cull);

        /*!
         * Triangle constructor.
         */
        Triangle(Point3 v0, Point3 v1, Point3 v2, bool back_facing_cull, Material* material);

        /*!
         * Triangle destructor.
         */
        ~Triangle();

        bool hit(Ray r, Vec3::RealType t_min, Vec3::RealType t_max, HitRecord& hr);

        glm::mat4 translate(glm::vec3 v);

        glm::mat4 rotate(glm::vec3 v);

        glm::mat4 scale(glm::vec3 v);

        void transform(std::list<std::tuple<Transformation, Vec3>> ts);
};

#endif /* _TRIANGLE_H_ */

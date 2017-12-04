#ifndef _PLANE_H_
#define _PLANE_H_

class Triangle;

#include <tuple>
#include "shape.h"

/*!
 * This class represents a box.
 */
class Plane : public Shape {

    private:
        // Plane origin
        Point3 origin;
        // Triangles
        Triangle* trs[2];

    public:
        /*!
         * Plane constructor.
         */
        Plane(Point3 p1, Point3 p2, Point3 p3, Point3 p4);

        /*!
         * Plane constructor.
         */
        Plane(Point3 p1, Point3 p2, Point3 p3, Point3 p4, Material* material);

        /*!
         * Plane destructor.
         */
        ~Plane();

        bool hit(Ray r, Vec3::RealType t_min, Vec3::RealType t_max, HitRecord& hr);

        glm::mat4 translate(glm::vec3 v);

        glm::mat4 rotate(glm::vec3 v);

        glm::mat4 scale(glm::vec3 v);

        void transform(std::list<std::tuple<Transformation, Vec3>> ts);
};

#endif /* _PLANE_H_ */

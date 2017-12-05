#ifndef _CUBE_H_
#define _CUBE_H_

#include <cmath>
#include "shape.h"

class Cube : public Shape {

    public:
        Point3 origin;
        Point3 end;
        /*!
         * Cube constructor.
         */
        Cube(Point3 origin, Point3 end);

        /*!
         * Cube constructor.
         */
        Cube(Point3 origin, Point3 end, Material* material);

        bool hit(Ray r, Vec3::RealType t_min, Vec3::RealType t_max, HitRecord& ht);

        void expand(Cube* cube);

        glm::mat4 translate(glm::vec3 v);

        glm::mat4 rotate(glm::vec3 v);

        glm::mat4 scale(glm::vec3 v);

        void transform(std::list<std::tuple<Transformation, Vec3>> ts);
};

#endif /* _CUBE_H_ */

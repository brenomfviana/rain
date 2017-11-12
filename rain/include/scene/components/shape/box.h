#ifndef _BOX_H_
#define _BOX_H_

class Triangle;

#include "shape.h"

/*!
 * This class represents a sphere.
 */
class Box : public Shape {

    private:
        // Box origin
        Point3 origin;
        // Size
        Vec3 size;
        // Triangles
        Triangle* trs[12];

    public:
        /*!
         * Box constructor.
         */
        Box(Point3 origin, Vec3 size);

        /*!
         * Box constructor.
         */
        Box(Point3 origin, Vec3 size, Material* material);

        /*!
         * Box destructor.
         */
        ~Box();

        bool hit(Ray r, Vec3::RealType t_min, Vec3::RealType t_max, HitRecord& hr);

        glm::mat4 translate(glm::vec3 v);

        glm::mat4 rotate(glm::vec3 v);

        glm::mat4 scale(glm::vec3 v);

        void transform(std::list<std::tuple<Transformation, Vec3>> ts);
};

#endif /* _BOX_H_ */

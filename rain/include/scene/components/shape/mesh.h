#ifndef _MESH_H_
#define _MESH_H_

class Box;
class Triangle;
class KDNode;

#include <list>
#include <tuple>
#include <vector>
#include "shape.h"
#include "scene/components/shape/kd_tree/kd_node.h"

#define EPSILON 0.00000001

/*!
 * This class represents a mesh of triangles.
 */
class Mesh : public Shape {

    private:
        // KD-Tree
        KDNode* root;
        // Triangles of mesh
        std::vector<Triangle*> trs;
        // Box
        Box* bbox;

    public:

        /*!
         * Mesh constructor.
         */
        Mesh(std::vector<Point3*> vs, std::vector<std::tuple<Vec3::RealType, Vec3::RealType, Vec3::RealType>*> fs);

        /*!
         * Mesh constructor.
         */
        Mesh(std::vector<Point3*> vs, std::vector<std::tuple<Vec3::RealType, Vec3::RealType, Vec3::RealType>*> fs,
            Material* material);

        /*!
         * Mesh destructor.
         */
        ~Mesh();

        bool hit(Ray r, Vec3::RealType t_min, Vec3::RealType t_max, HitRecord& hr);

        glm::mat4 translate(glm::vec3 v);

        glm::mat4 rotate(glm::vec3 v);

        glm::mat4 scale(glm::vec3 v);

        void transform(std::list<std::tuple<Transformation, Vec3>> ts);
};

#endif /* _MESH_H_ */

#include <limits>
#include "scene/components/shape/mesh.h"
#include "scene/components/shape/triangle.h"

Mesh::Mesh(std::vector<Point3*> vs, std::vector<std::tuple<Vec3::RealType, Vec3::RealType, Vec3::RealType>*> fs)
        : Shape(*(vs[0])) {
    // Build mesh
    int i, j, k;
    for (std::tuple<Vec3::RealType, Vec3::RealType, Vec3::RealType>* &f : fs) {
        std::tie(i, j, k) = *f;
        Triangle* t = new Triangle(*(vs[i]), *(vs[j]), *(vs[k]), true);
        this->trs.push_back(t);
    }
    // Build kd-tree
    this->root = this->root->build(this->trs, 0);
}

Mesh::Mesh(std::vector<Point3*> vs, std::vector<std::tuple<Vec3::RealType, Vec3::RealType, Vec3::RealType>*> fs,
        Material* material) : Shape(*(vs[0]), material) {
    // Build mesh
    int i, j, k;
    for (std::tuple<Vec3::RealType, Vec3::RealType, Vec3::RealType>* &f : fs) {
        std::tie(i, j, k) = *f;
        Triangle* t = new Triangle(*(vs[i - 1]), *(vs[j - 1]), *(vs[k - 1]), true, material);
        this->trs.push_back(t);
    }
    // Build kd-tree
    this->root = this->root->build(this->trs, 0);
    std::cout << this->root->bbox->size << "\n";
}

/*!
 * Mesh destructor.
 */
Mesh::~Mesh() {
    /* empty */
}

bool Mesh::hit(Ray r, Vec3::RealType t_min, Vec3::RealType t_max, HitRecord& hr) {
    // Check hit
    return this->root->hit(this->root, r, t_min, t_max, hr);
}

glm::mat4 Mesh::translate(glm::vec3 v) {
    (void) v;
    return glm::mat4(1.f);
}

glm::mat4 Mesh::rotate(glm::vec3 v) {
    (void) v;
    return glm::mat4(1.f);
}

glm::mat4 Mesh::scale(glm::vec3 v) {
    (void) v;
    return glm::mat4(1.f);
}

void Mesh::transform(std::list<std::tuple<Transformation, Vec3>> ts) {
    // Check if the list is not empty
    if (!ts.empty()) {
        for (Triangle* t : trs) {
            (*t).transform(ts);
        }
    }
}

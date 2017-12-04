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
    // Build box
    Vec3::RealType inf = std::numeric_limits<Vec3::RealType>::infinity();
    Vec3::RealType xmin = inf, xmax = -inf;
    Vec3::RealType ymin = inf, ymax = -inf;
    Vec3::RealType zmin = inf, zmax = -inf;
    for (Point3* p : vs) {
        xmin = std::min(p->x(), xmin);
        ymin = std::min(p->y(), ymin);
        zmin = std::min(p->z(), zmin);
        xmax = std::max(p->x(), xmax);
        ymax = std::max(p->y(), ymax);
        zmax = std::max(p->z(), zmax);
    }
    Point3 bbox_origin = Point3(xmin, ymin, zmin);
    Vec3::RealType bbox_xsize = (bbox_origin - Vec3(xmax, ymin, zmin)).length();
    Vec3::RealType bbox_ysize = (bbox_origin - Vec3(xmin, ymax, zmin)).length();
    Vec3::RealType bbox_zsize = (bbox_origin - Vec3(xmin, ymin, zmax)).length();
    Vec3 bbox_size = Vec3(bbox_xsize, bbox_ysize, bbox_zsize);
    this->bbox = new Box(bbox_origin, bbox_size);
    // Build kd-tree
    this->root = this->root->build(trs, 0);
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
    // Build box
    Vec3::RealType inf = std::numeric_limits<Vec3::RealType>::infinity();
    Vec3::RealType xmin = inf, xmax = -inf;
    Vec3::RealType ymin = inf, ymax = -inf;
    Vec3::RealType zmin = inf, zmax = -inf;
    for (Point3* p : vs) {
        xmin = std::min(p->x(), xmin);
        ymin = std::min(p->y(), ymin);
        zmin = std::min(p->z(), zmin);
        xmax = std::max(p->x(), xmax);
        ymax = std::max(p->y(), ymax);
        zmax = std::max(p->z(), zmax);
    }
    Point3 bbox_origin = Point3(xmin, ymin, zmin);
    Vec3::RealType bbox_xsize = (bbox_origin - Vec3(xmax, ymin, zmin)).length();
    Vec3::RealType bbox_ysize = (bbox_origin - Vec3(xmin, ymax, zmin)).length();
    Vec3::RealType bbox_zsize = (bbox_origin - Vec3(xmin, ymin, zmax)).length();
    Vec3 bbox_size = Vec3(bbox_xsize, bbox_ysize, bbox_zsize);
    this->bbox = new Box(bbox_origin, bbox_size);
    // Build kd-tree
    this->root = this->root->build(trs, 0);
}

/*!
 * Mesh destructor.
 */
Mesh::~Mesh() {
    /* empty */
}

bool Mesh::hit(Ray r, Vec3::RealType t_min, Vec3::RealType t_max, HitRecord& hr) {
    // Check hit
    if (this->bbox->hit(r, t_min, t_max, hr)) {
        return this->root->hit(this->root, r, t_min, t_max, hr);
    }
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
    bbox->transform(ts);
}

#include "scene/components/shape/plane.h"
#include "scene/components/shape/triangle.h"

Plane::Plane(Point3 p1, Point3 p2, Point3 p3, Point3 p4) : Shape(p1) {
    // Create box
    Triangle* t0 = new Triangle(p4, p1, p2, false);
    trs[0] = t0;
    Triangle* t1 = new Triangle(p4, p2, p3, false);
    trs[1] = t1;
}

Plane::Plane(Point3 p1, Point3 p2, Point3 p3, Point3 p4, Material* material) :
        Shape(p1, material) {
    // Create box
    Triangle* t0 = new Triangle(p4, p1, p2, false, material);
    trs[0] = t0;
    Triangle* t1 = new Triangle(p4, p2, p3, false, material);
    trs[1] = t1;
}

Plane::~Plane() {
    /* empty */
}

bool Plane::hit(Ray r, Vec3::RealType t_min, Vec3::RealType t_max, HitRecord& hr) {
    // Check hit
    for (Triangle* t : trs) {
        if ((*t).hit(r, t_min, t_max, hr)) {
            return true;
        }
    }
}

glm::mat4 Plane::translate(glm::vec3 v) {
    (void) v;
    return glm::mat4(1.f);
}

glm::mat4 Plane::rotate(glm::vec3 v) {
    (void) v;
    return glm::mat4(1.f);
}

glm::mat4 Plane::scale(glm::vec3 v) {
    (void) v;
    return glm::mat4(1.f);
}

void Plane::transform(std::list<std::tuple<Transformation, Vec3>> ts) {
    // Check if the list is not empty
    if (!ts.empty()) {
        for (Triangle* t : trs) {
            (*t).transform(ts);
        }
    }
}

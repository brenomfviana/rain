#include "scene/components/shape/box.h"
#include "scene/components/shape/triangle.h"

/*!
 * Box constructor.
 */
Box::Box(Point3 origin, Vec3 size) : Shape(origin) {
    this->size = size;
    Point3 sx = Point3(size.x(), 0, 0);
    Point3 sy = Point3(0, size.y(), 0);
    Point3 sz = Point3(0, 0, size.z());
    // Create box
    Triangle* t0 = new Triangle(origin, origin + sx, origin + sy, true);
    trs[0] = t0;
    Triangle* t1 = new Triangle(origin + sx, origin + sx + sy, origin + sy, true);
    trs[1] = t1;
    Triangle* t2 = new Triangle(origin + sx, origin + sx + sz, origin + sx + sy, true);
    trs[2] = t2;
    Triangle* t3 = new Triangle(origin + sx + sz, origin + sz + sy + sz, origin + sx + sy, true);
    trs[3] = t3;
    Triangle* t4 = new Triangle(origin + sx + sz, origin + sz, origin + sx + sy + sz, true);
    trs[4] = t4;
    Triangle* t5 = new Triangle(origin + sz, origin + sy + sz, origin + sx + sy + sy, true);
    trs[5] = t5;
    Triangle* t6 = new Triangle(origin + sz, origin, origin + sy + sz, true);
    trs[6] = t6;
    Triangle* t7 = new Triangle(origin, origin + sy, origin + sy + sz, true);
    trs[7] = t7;
    Triangle* t8 = new Triangle(origin, origin + sz, origin + sx + sz, true);
    trs[8] = t8;
    Triangle* t9 = new Triangle(origin + sx + sz, origin + sx, origin, true);
    trs[9] = t9;
    Triangle* tA = new Triangle(origin + sy, origin + sx + sy, origin + sy + sz, true);
    trs[10] = tA;
    Triangle* tB = new Triangle(origin + sx + sy, origin + sx + sy + sz, origin + sy + sz, true);
    trs[11] = tB;
}

/*!
 * Box constructor.
 */
Box::Box(Point3 origin, Vec3 size, Material* material) :
        Shape(origin, material) {
    this->size = size;
    Point3 sx = Point3(size.x(), 0, 0);
    Point3 sy = Point3(0, size.y(), 0);
    Point3 sz = Point3(0, 0, size.z());
    // Create box
    Triangle* t0 = new Triangle(origin, origin + sx, origin + sy, true, material);
    trs[0] = t0;
    Triangle* t1 = new Triangle(origin + sx, origin + sx + sy, origin + sy, true, material);
    trs[1] = t1;
    Triangle* t2 = new Triangle(origin + sx, origin + sx + sz, origin + sx + sy, true, material);
    trs[2] = t2;
    Triangle* t3 = new Triangle(origin + sx + sz, origin + sz + sy + sz, origin + sx + sy, true, material);
    trs[3] = t3;
    Triangle* t4 = new Triangle(origin + sx + sz, origin + sz, origin + sx + sy + sz, true, material);
    trs[4] = t4;
    Triangle* t5 = new Triangle(origin + sz, origin + sy + sz, origin + sx + sy + sy, true, material);
    trs[5] = t5;
    Triangle* t6 = new Triangle(origin + sz, origin, origin + sy + sz, true, material);
    trs[6] = t6;
    Triangle* t7 = new Triangle(origin, origin + sy, origin + sy + sz, true, material);
    trs[7] = t7;
    Triangle* t8 = new Triangle(origin, origin + sz, origin + sx + sz, true, material);
    trs[8] = t8;
    Triangle* t9 = new Triangle(origin + sx + sz, origin + sx, origin, true, material);
    trs[9] = t9;
    Triangle* tA = new Triangle(origin + sy, origin + sx + sy, origin + sy + sz, true, material);
    trs[10] = tA;
    Triangle* tB = new Triangle(origin + sx + sy, origin + sx + sy + sz, origin + sy + sz, true, material);
    trs[11] = tB;
}

/*!
 * Box destructor.
 */
Box::~Box() {
    /* empty */
}

bool Box::hit(Ray r, Vec3::RealType t_min, Vec3::RealType t_max, HitRecord& hr) {
    bool reached = false;
    // Check hit
    for (Triangle* t : trs) {
        if ((*t).hit(r, t_min, t_max, hr)) {
            reached = true;
            break;
        }
    }
    return reached;
}

glm::mat4 Box::translate(glm::vec3 v) {
    (void) v;
    return glm::mat4(1.f);
}

glm::mat4 Box::rotate(glm::vec3 v) {
    (void) v;
    return glm::mat4(1.f);
}

glm::mat4 Box::scale(glm::vec3 v) {
    (void) v;
    return glm::mat4(1.f);
}

void Box::transform(std::list<std::tuple<Transformation, Vec3>> ts) {
    // Check if the list is not empty
    if (!ts.empty()) {
        for (Triangle* t : trs) {
            (*t).transform(ts);
        }
    }
}

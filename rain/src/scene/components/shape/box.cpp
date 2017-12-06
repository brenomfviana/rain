#include "scene/components/shape/box.h"

Box::Box(Point3 origin, Vec3 size) : Shape(origin) {
    this->size = size;
    Point3 x = Point3(size.x(), 0, 0);
    Point3 y = Point3(0, size.y(), 0);
    Point3 z = Point3(0, 0, size.z());
    this->o = origin;
    this->end = o + x + y + z;
    // Create box
    Triangle* t0 = new Triangle(o, o + y, o + x);
    this->trs[0] = t0;
    Triangle* t1 = new Triangle(o + x, o + y, o + x + y);
    this->trs[1] = t1;
    Triangle* t2 = new Triangle(o, o + x + z, o + z);
    this->trs[2] = t2;
    Triangle* t3 = new Triangle(o, o + x, o + x + z);
    this->trs[3] = t3;
    Triangle* t4 = new Triangle(o, o + z, o + y + z);
    this->trs[4] = t4;
    Triangle* t5 = new Triangle(o, o + y + z, o + y);
    this->trs[5] = t5;
    Triangle* t6 = new Triangle(o + x, o + x + y, o + x + z);
    this->trs[6] = t6;
    Triangle* t7 = new Triangle(o + x + y, o + x + y + z, o + x + z);
    this->trs[7] = t7;
    Triangle* t8 = new Triangle(o + y, o + y + z, o + x + y);
    this->trs[8] = t8;
    Triangle* t9 = new Triangle(o + y + z, o + x + y + z, o + x + y);
    this->trs[9] = t9;
    Triangle* tA = new Triangle(o + y + z, o + z, o + x + y + z);
    this->trs[10] = tA;
    Triangle* tB = new Triangle(o + z, o + x + z, o + x + y + z);
    this->trs[11] = tB;
}

Box::Box(Point3 origin, Vec3 size, Material* material) : Shape(origin, material) {
    this->size = size;
    Point3 x = Point3(size.x(), 0, 0);
    Point3 y = Point3(0, size.y(), 0);
    Point3 z = Point3(0, 0, size.z());
    this->o = origin;
    this->end = o + x + y + z;
    // Create box
    Triangle* t0 = new Triangle(o, o + y, o + x, material);
    this->trs[0] = t0;
    Triangle* t1 = new Triangle(o + x, o + y, o + x + y, material);
    this->trs[1] = t1;
    Triangle* t2 = new Triangle(o, o + x + z, o + z, material);
    this->trs[2] = t2;
    Triangle* t3 = new Triangle(o, o + x, o + x + z, material);
    this->trs[3] = t3;
    Triangle* t4 = new Triangle(o, o + z, o + y + z, material);
    this->trs[4] = t4;
    Triangle* t5 = new Triangle(o, o + y + z, o + y, material);
    this->trs[5] = t5;
    Triangle* t6 = new Triangle(o + x, o + x + y, o + x + z, material);
    this->trs[6] = t6;
    Triangle* t7 = new Triangle(o + x + y, o + x + y + z, o + x + z, material);
    this->trs[7] = t7;
    Triangle* t8 = new Triangle(o + y, o + y + z, o + x + y, material);
    this->trs[8] = t8;
    Triangle* t9 = new Triangle(o + y + z, o + x + y + z, o + x + y, material);
    this->trs[9] = t9;
    Triangle* tA = new Triangle(o + y + z, o + z, o + x + y + z, material);
    this->trs[10] = tA;
    Triangle* tB = new Triangle(o + z, o + x + z, o + x + y + z, material);
    this->trs[11] = tB;
}

Box::~Box() {
    /* empty */
}

bool Box::hit(Ray r, Vec3::RealType t_min, Vec3::RealType t_max, HitRecord& hr) {
    // Check hit
    for (Triangle* t : this->trs) {
        if ((*t).hit(r, t_min, t_max, hr)) {
            return true;
        }
    }
}

Box* Box::expand(Box* box) {
    //
    Vec3::RealType xmin = std::min(box->origin.x(), this->origin.x());
    Vec3::RealType ymin = std::min(box->origin.y(), this->origin.y());
    Vec3::RealType zmin = std::min(box->origin.z(), this->origin.z());
    Vec3::RealType xmax = std::max(box->end.x(), this->end.x());
    Vec3::RealType ymax = std::max(box->end.y(), this->end.y());
    Vec3::RealType zmax = std::max(box->end.z(), this->end.z());
    Point3 bbox_origin = Point3(xmin, ymin, zmin);
    Vec3::RealType bbox_xsize = (bbox_origin - Vec3(xmax, ymin, zmin)).length();
    Vec3::RealType bbox_ysize = (bbox_origin - Vec3(xmin, ymax, zmin)).length();
    Vec3::RealType bbox_zsize = (bbox_origin - Vec3(xmin, ymin, zmax)).length();
    Vec3 bbox_size = Vec3(bbox_xsize, bbox_ysize, bbox_zsize);
    //
    return (new Box(bbox_origin, bbox_size));
}

int Box::longest_axis() {
    if (this->size.x() >= this->size.y()) {
        if (this->size.x() >= this->size.z()) {
            return 0;
        } else {
            return 2;
        }
    } else if (this->size.y() >= this->size.z()) {
        return 1;
    } else {
        return 2;
    }
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
        for (Triangle* t : this->trs) {
            (*t).transform(ts);
        }
    }
}

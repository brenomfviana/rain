#include "scene/components/light/point_light.h"

PointLight::PointLight(Vec3 origin, Vec3 intensity) : Light(intensity) {
    this->origin = origin;
}

PointLight::~PointLight() {
    /* empty */
}

Vec3 PointLight::get_origin() const {
    return this->origin;
}

Vec3 PointLight::get_direction(Point3 p) const {
    return this->origin - p;
}

Vec3 PointLight::get_intensity(Point3 p) const {
    (void) p;
    return this->intensity;
}

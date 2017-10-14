#include "scene/components/light/directional_light.h"

DirectionalLight::DirectionalLight(Vec3 direction, Vec3 intensity) : Light(intensity) {
    this->direction = direction;
}

DirectionalLight::~DirectionalLight() {
    /* empty */
}

Vec3 DirectionalLight::get_direction(Point3 p) const {
    (void) p;
    return this->direction;
}

Vec3 DirectionalLight::get_intensity(Point3 p) const {
    (void) p;
    return this->intensity;
}

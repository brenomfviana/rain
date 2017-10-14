#include "scene/components/light/spotlight.h"

Spotlight::Spotlight(Point3 origin, Vec3 direction, Vec3 intensity, float beam_angle) :
        PointLight(origin, intensity) {
    this->direction  = direction;
    this->beam_angle = beam_angle;
}

Spotlight::~Spotlight() {
    /* empty */
}

Vec3 Spotlight::get_direction(Point3 p) const {
    Vec3 dir = this->origin - p;
    float angle = dot(-this->direction, dir) / ((-this->direction).length() * dir.length());
    if (angle >= this->beam_angle) {
        return dir;
    }
    return Vec3(0, 0, 0);
}

Vec3 Spotlight::get_intensity(Point3 p) const {
    (void) p;
    return this->intensity;
}

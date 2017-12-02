#include "scene/components/shape/materials/lambertian_material.h"

LambertianMaterial::LambertianMaterial(Texture* albedo) {
    this->albedo = albedo;
}

LambertianMaterial::~LambertianMaterial() {
    /* empty */
}

Vec3 LambertianMaterial::random_in_unit_sphere() const {
    Vec3 p;
    do {
        p = 2.0 * Vec3(drand48(), drand48(), drand48()) - Vec3(1, 1, 1);
    } while (dot(p, p) >= 1.0);
    return p;
}

bool LambertianMaterial::scatter(const Ray& r, const HitRecord& hr,
        RGB& attenuation, Ray& sray) const {
    (void) (r);
    Vec3 target = hr.point + hr.normal + random_in_unit_sphere();
    sray = Ray(hr.point, target - hr.point);
    attenuation = this->albedo->value(0, 0, hr.point);
    return true;
}

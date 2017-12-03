#include "scene/components/shape/materials/diffuse_light_material.h"

DiffuseLightMaterial::DiffuseLightMaterial(RGB emit) {
    this->emit = emit;
}

DiffuseLightMaterial::~DiffuseLightMaterial() {
    /* empty */
}

bool DiffuseLightMaterial::scatter(const Ray& r, const HitRecord& hr, RGB& attenuation,
        Ray& sray) const {
    (void) r;
    (void) hr;
    (void) attenuation;
    (void) sray;
    return false;
}

Vec3 DiffuseLightMaterial::emitted(Vec3::RealType u, Vec3::RealType v, const Vec3& p) const {
    (void) u;
    (void) v;
    (void) p;
    return this->emit;
}

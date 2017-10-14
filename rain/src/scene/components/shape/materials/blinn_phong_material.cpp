#include "scene/components/shape/materials/blinn_phong_material.h"

BlinnPhongMaterial::BlinnPhongMaterial(Vec3 ka, Vec3 kd, Vec3 ks, Vec3::RealType p) {
    this->ka = ka;
    this->kd = kd;
    this->ks = ks;
    this->p  =  p;
}

BlinnPhongMaterial::~BlinnPhongMaterial() {
    /* empty */
}

bool BlinnPhongMaterial::scatter(const Ray& r, const HitRecord& hr,
        RGB& attenuation, Ray& sray) const {
    (void) (hr);
    sray = r;
    // No attenuation
    attenuation = Vec3(1, 1, 1);
    return true;
}

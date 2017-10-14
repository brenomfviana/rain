#include "scene/components/shape/materials/toon_material.h"

ToonMaterial::ToonMaterial(std::vector<RGB> colors, std::vector<Vec3::RealType> angles) {
    this->colors = colors;
    this->angles = angles;
}

ToonMaterial::~ToonMaterial() {
    /* empty */
}

bool ToonMaterial::scatter (const Ray& r, const HitRecord& hr, RGB& attenuation,
        Ray& sray) const {
    (void) (hr);
    sray = r;
    // No attenuation
    attenuation = Vec3(1, 1, 1);
    return true;
}

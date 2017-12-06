#include "scene/components/shape/materials/perlin_texture.h"

PerlinTexture::PerlinTexture() {
    this->scale = 0;
}

PerlinTexture::PerlinTexture(Vec3::RealType scale) {
    this->scale = scale;
}

PerlinTexture::~PerlinTexture() {
    /* empty */
}

RGB PerlinTexture::value(Vec3::RealType u, Vec3::RealType v, const Vec3& p) const {
    (void) u;
    (void) v;
    return Vec3(1, 1, 1) * 0.5 * (1 + std::sin(this->scale * p.x() +
            5 * this->noise.turb(this->scale * p)));
}

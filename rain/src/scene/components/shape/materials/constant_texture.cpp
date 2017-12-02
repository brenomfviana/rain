#include "scene/components/shape/materials/constant_texture.h"

ConstantTexture::ConstantTexture() {
    /* empty */
}

ConstantTexture::~ConstantTexture() {
    /* empty */
}

ConstantTexture::ConstantTexture(RGB color) {
    this->color = color;
}

RGB ConstantTexture::value(Vec3::RealType u, Vec3::RealType v, const Vec3& p) const {
    return this->color;
}

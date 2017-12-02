#include "scene/components/shape/materials/checker_texture.h"
#include <cmath>

CheckerTexture::CheckerTexture() {
    /* empty */
}

CheckerTexture::~CheckerTexture() {
    /* empty */
}

CheckerTexture::CheckerTexture(Texture* odd, Texture* even) {
    this->odd  = odd;
    this->even = even;
}

RGB CheckerTexture::value(Vec3::RealType u, Vec3::RealType v, const Vec3& p) const {
    Vec3::RealType sines = std::sin(10 * p.x()) * std::sin(10 * p.y()) * std::sin(10 * p.z());
	if (sines < 0) {
		return odd->value(u, v, p);
	} else {
		return even->value(u, v, p);
	}
}

#include "render/shader/depth_map_shader.h"

DepthMapShader::DepthMapShader(Vec3::RealType max_depth, RGB foreground, RGB background) {
    this->max_depth  = max_depth;
    this->foreground = foreground;
    this->background = background;
}

DepthMapShader::~DepthMapShader() {
    /* empty */
}

RGB DepthMapShader::color(const Ray& r, const Scene& scene, int nrays) const {
    (void) (nrays);
    // Check hit
    HitRecord hr;
    if (intersect(r, scene, 0, 10, hr)) {
        // Check depth
        if (hr.t >= 0 && hr.t <= this->max_depth) {
            Vec3::RealType t = hr.t / this->max_depth;
            return (this->foreground * (1 - t)) + (this->background * t);
        }
    }
    return this->background;
}

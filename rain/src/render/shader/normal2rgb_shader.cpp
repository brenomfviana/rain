#include "render/shader/normals2rgb_shader.h"

RGB Normals2RGBShader::color(const Ray& r, const Scene& scene, int nrays) const {
    (void) (nrays);
    // Check hit
    HitRecord hr;
    if (intersect(r, scene, 0, 10, hr)) {
        // Normal 2 RGB
        return ((hr.normal + Vec3(1, 1, 1)) * 0.5);
    } else {
        return background(r, scene);
    }
}

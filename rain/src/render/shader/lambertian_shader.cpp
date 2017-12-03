#include "render/shader/lambertian_shader.h"

RGB LambertianShader::color(const Ray& r, const Scene& scene, int nrays) const {
    // Check hit
    HitRecord hr;
    if (intersect(r, scene, 0.001, 10, hr)) {
        //
        Ray sray;
        RGB attenuation;
        RGB emitted = hr.material->emitted(0, 0, hr.point);
        // Check if the ray will be scattered
        if (nrays > 0 && hr.material->scatter(r, hr, attenuation, sray)) {
            // Get the color from where the scattered ray reaches
            return emitted + attenuation * color(sray, scene, nrays - 1);
        }
        return emitted;
    } else {
        return background(r, scene);
    }
}

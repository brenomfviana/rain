#include "render/shader/lambertian_shader.h"

RGB LambertianShader::color(const Ray& r, const Scene& scene, int nrays) const {
    // Check if recursion is over
    if (nrays-- == 0) {
        return RGB(1, 1, 1);
    } else {
        // Check hit
        HitRecord hr;
        if (intersect(r, scene, 0, 10, hr)) {
            //
            Ray scatteredRay;
            RGB attenuation;
            // Shape material
            Material* m = hr.material;
            // Check if the ray will be scattered
            if (m->scatter(r, hr, attenuation, scatteredRay)) {
                // Get the color from where the scattered ray reaches
                return attenuation * color(scatteredRay, scene, nrays);
            }
            return RGB(1, 1, 1);
        } else {
            return background(r, scene);
        }
    }
}

#include "render/shader/toon_shader.h"

ToonShader::ToonShader(RGB border_color) {
    this->border_color = border_color;
}

ToonShader::~ToonShader() {
    /* empty */
}

RGB ToonShader::color(const Ray& r, const Scene& scene, int nrays) const {
    (void) nrays;
    // Check hit
    HitRecord hr;
    if (intersect(r, scene, 0, 10, hr)) {
        // Check if is a border
        Vec3::RealType borderAngle = dot(unit_vector(-r.get_direction()), hr.normal) /
            ((-r.get_direction()).length() * hr.normal.length());
        if (borderAngle < 0.1736) {
            return border_color;
        }
        // Get Toon material
        ToonMaterial* material = dynamic_cast<ToonMaterial*>(hr.material);
        RGB c;
        // Lighting
        HitRecord shr;
        Vec3::RealType pickedAngle = material->angles.size();
        for (auto& light : scene.lights) {
            // Check angle and get correspondent color
            Vec3 l = light->get_direction(hr.point) - r.get_direction();
            Vec3::RealType angle = dot(hr.normal, l) / (hr.normal.length() * l.length());
            //
            for (int i = material->angles.size() - 1; i >= 0; i--) {
                if ((i == 0 && angle >= material->angles[i] && pickedAngle > i) ||
                        (angle <= material->angles[i - 1] &&
                         angle >= material->angles[i] && pickedAngle > i)) {
                    pickedAngle = i;
                    c = material->colors[i];
                }
            }
        }
        return (c / scene.lights.size());
    } else {
        return background(r, scene);
    }
}

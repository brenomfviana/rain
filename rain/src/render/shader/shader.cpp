#include "render/shader/shader.h"

RGB Shader::background(const Ray& r, const Scene& scene) const {
    // Get background corners colors
    RGB ul = scene.background.upper_left;
    RGB ll = scene.background.lower_left;
    RGB ur = scene.background.upper_right;
    RGB lr = scene.background.lower_right;
    // Bilinear interpolation
    Vec3 rd = r.get_direction();
    Vec3::RealType x = (rd.x() * 0.25) + 0.5;
    Vec3::RealType y = (rd.y() * 0.5)  + 0.5;
    return (1 - y) * ((1 - x) * ll + x * lr) +
                y  * ((1 - x) * ul + x * ur);
}

bool Shader::intersect(const Ray& r, const Scene& scene, const Vec3::RealType tMin,
        const Vec3::RealType tMax, HitRecord& hr) const {
    // Temp distance
    hr.t = std::numeric_limits<Vec3::RealType>::infinity();
    // Check if hit scene components
    for (auto& shape : scene.components) {
        HitRecord haux;
        if (shape->hit(r, tMin, tMax, haux)) {
            // Check which object is in front
            if (haux.t > -1 && hr.t > haux.t) {
                hr.t = haux.t;
                hr.point = haux.point;
                hr.normal = haux.normal;
                hr.material = haux.material;
            }
        }
    }
    return ((hr.t > 0) && (hr.t < std::numeric_limits<Vec3::RealType>::infinity()));
}

#include "render/shader/shader.h"
#include <cmath>

RGB Shader::background(const Ray& r, const Scene& scene) const {
    // Get background corners colors
    RGB ul = scene.background.upper_left;
    RGB ll = scene.background.lower_left;
    RGB ur = scene.background.upper_right;
    RGB lr = scene.background.lower_right;
    // Bilinear interpolation
    Vec3 rd = r.get_direction();
    Vec3::RealType x = (rd.x() * 0.25) + 0.5;
    x =  std::max(Vec3::RealType(0.f), x);
    Vec3::RealType y = (rd.y() * 0.5)  + 0.5;
    y =  std::max(Vec3::RealType(0.f), y);
    return (1 - y) * ((1 - x) * ll + x * lr) +
                y  * ((1 - x) * ul + x * ur);
}

bool Shader::intersect(const Ray& r, const Scene& scene, const Vec3::RealType t_min,
        const Vec3::RealType t_max, HitRecord& hr) const {
    // Temp distance
    hr.t = std::numeric_limits<Vec3::RealType>::infinity();
    Vec3::RealType closest_so_far = t_max;
    // Check if hit scene components
    for (auto& shape : scene.components) {
        HitRecord haux;
        if (shape->hit(r, t_min, closest_so_far, haux)) {
                closest_so_far = haux.t;
                hr.t        = haux.t;
                hr.point    = haux.point;
                hr.normal   = haux.normal;
                hr.material = haux.material;
        }
    }
    return ((hr.t > 0) && (hr.t < std::numeric_limits<Vec3::RealType>::infinity()));
}

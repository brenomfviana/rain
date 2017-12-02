#include "scene/components/shape/materials/metal_material.h"

MetalMaterial::MetalMaterial(RGB albedo, Vec3::RealType fuzz) {
    this->albedo = albedo;
    this->fuzz   = fuzz;
}

MetalMaterial::~MetalMaterial() {
    /* empty */
}

Vec3 MetalMaterial::random_in_unit_sphere() const {
    Vec3 p;
    do {
        p = 2.0 * Vec3(drand48(), drand48(), drand48()) - Vec3(1, 1, 1);
    } while (dot(p, p) >= 1.0);
    return p;
}

Vec3 MetalMaterial::reflect(const Vec3& v, const Vec3& n) const {
    return v - 2 * dot(v, n) * n;
}

bool MetalMaterial::scatter(const Ray& r, const HitRecord& hr,
        RGB& attenuation, Ray& sray) const {
    Vec3 reflected = reflect(unit_vector(r.get_direction()), hr.normal);
    sray = Ray(hr.point, reflected + this->fuzz * random_in_unit_sphere());
    attenuation = this->albedo;
    return (dot(sray.get_direction(), hr.normal) > 0);
}

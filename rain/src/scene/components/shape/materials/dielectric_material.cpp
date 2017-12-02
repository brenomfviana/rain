#include "scene/components/shape/materials/dielectric_material.h"

DielectricMaterial::DielectricMaterial(Vec3::RealType ri) {
    this->ri = ri;
}

DielectricMaterial::~DielectricMaterial() {
    /* empty */
}

Vec3::RealType DielectricMaterial::schlick(Vec3::RealType cosine, Vec3::RealType ri) const {
    Vec3::RealType r = (1.f - ri) / (1.f + ri);
    r = r * r;
    return (r + (1.f - r) * std::pow((1.f - cosine), 5.f));
}

bool DielectricMaterial::refract(const Vec3& v, const Vec3& n, Vec3::RealType ni_over_nt,
        Vec3& refracted) const {
    //
    Vec3 uv = unit_vector(v);
    Vec3::RealType dt = dot(uv, n);
    //
    Vec3::RealType discriminant = 1.f - (ni_over_nt * ni_over_nt * (1.f - (dt * dt)));
    //
    if (discriminant > 0.f) {
        // refracted = (dt * v) + (dt * std::sqrt(discriminant) - std::sqrt(discriminant)) * n;
        refracted = ((ni_over_nt * (uv - n * dt)) - (n * std::sqrt(discriminant)));
        return true;
    } else {
        return false;
    }
}

Vec3 DielectricMaterial::reflect(const Vec3& v, const Vec3& n) const {
    return (v - (2 * (dot(v, n) * n)));
}

bool DielectricMaterial::scatter(const Ray& r, const HitRecord& hr,
        RGB& attenuation, Ray& sray) const {
    //
    attenuation = Vec3(1.f, 1.f, 1.f);
    //
    Vec3::RealType ni_over_nt;
    Vec3::RealType cosine;
    //
    Vec3 outward_normal;
    //
    Vec3::RealType d = dot(r.get_direction(), hr.normal);
    if (d > 0) {
        outward_normal = -hr.normal;
        ni_over_nt = this->ri;
        cosine = (d / r.get_direction().length());
        cosine = std::sqrt(1 - ((this->ri * this->ri) * (1 - (cosine * cosine))));
    } else {
        outward_normal = hr.normal;
        ni_over_nt = (1.f / this->ri);
        cosine = -(d / r.get_direction().length());
    }
    //
    Vec3 refracted;
    Vec3::RealType reflect_prob;
    //
    if (refract(r.get_direction(), outward_normal, ni_over_nt, refracted)) {
        reflect_prob = schlick(cosine, this->ri);
    } else {
        reflect_prob = 1.f;
    }
    //
    if (drand48() < reflect_prob) {
        sray = Ray(hr.point, reflect(r.get_direction(), hr.normal));
    } else {
        sray = Ray(hr.point, refracted);
    }
    return true;
}

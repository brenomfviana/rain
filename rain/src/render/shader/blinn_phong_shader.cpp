#include "render/shader/blinn_phong_shader.h"

BlinnPhongShader::BlinnPhongShader(RGB alight) {
    this->alight = alight;
}

BlinnPhongShader::~BlinnPhongShader() {
    /* empty */
}

RGB BlinnPhongShader::color(const Ray& r, const Scene& scene, int nrays) const {
    (void) nrays;
    // Check hit
    HitRecord hr;
    if (intersect(r, scene, 0, 10, hr)) {
        // Get Blinn-Phong material
        BlinnPhongMaterial* material = dynamic_cast<BlinnPhongMaterial*>(hr.material);
        // Ambient light on the shape
        RGB c = material->ka * this->alight;
        // Lighting
        HitRecord shr;
        Vec3::RealType t = 10;
        for (Light* light : scene.lights) {
            if (typeid(*light) == typeid(PointLight)) {
                PointLight* l = dynamic_cast<PointLight*>(light);
                t = (l->get_origin() - hr.point).length();
            } else if (typeid(*light) == typeid(Spotlight)) {
                Spotlight* l = dynamic_cast<Spotlight*>(light);
                t = (l->get_origin() - hr.point).length();
            }
            // Check shadows
            if (!intersect(Ray(hr.point, unit_vector(light->get_direction(hr.point))),
                    scene, 0, t, shr)) {
                c += blinnPhong(r, light, hr);
            }
        }
        // Fix specular
        c = RGB(std::min<Vec3::RealType>(1.f, Vec3::RealType(c.r())),
                std::min<Vec3::RealType>(1.f, Vec3::RealType(c.g())),
                std::min<Vec3::RealType>(1.f, Vec3::RealType(c.b())));
        // Return resulting color
        return c;
    } else {
        return background(r, scene);
    }
}

RGB BlinnPhongShader::blinnPhong(const Ray& r, const Light* light, HitRecord& hr) const {
    BlinnPhongMaterial* material = dynamic_cast<BlinnPhongMaterial*>(hr.material);
    // Unitary light direction
    Vec3 ul = unit_vector(light->get_direction(hr.point));
    // Lambertian
    Vec3::RealType lambertian = std::max<Vec3::RealType>(0.f, dot(ul, hr.normal));
    // Blinn-Phong
    Vec3 H = unit_vector(ul + unit_vector(-r.get_direction()));
    // N.H
    Vec3::RealType specular = std::max<Vec3::RealType>(0.f, dot(hr.normal, H));
    specular = std::pow(specular, material->p);
    //
    Vec3 intensity = light->get_intensity(hr.point);
    return (material->kd * lambertian * intensity +
            material->ks *  specular  * intensity);
}

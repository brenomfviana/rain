#include "scene/components/shape/sphere.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Sphere::Sphere(Point3 origin, Vec3::RealType radius) : Shape(origin) {
    this->radius = radius;
}

Sphere::Sphere(Point3 origin, Vec3::RealType radius, Material* material) :
        Shape(origin, material) {
    this->radius = radius;
}

Sphere::~Sphere() {
    /* empty */
}

bool Sphere::hit(Ray r, Vec3::RealType t_min, Vec3::RealType t_max, HitRecord& hr) {
    Vec3 oc = r.get_origin() - this->origin;
    Vec3::RealType a = dot(r.get_direction(), r.get_direction());
    Vec3::RealType b = 2 * dot(oc, r.get_direction());
    Vec3::RealType c = dot(oc, oc) - (this->radius * this->radius);
    Vec3::RealType delta = (b * b - 4 * a * c);
    // Check if the ray hit this sphere
    if (delta >= 0) {
        // Get smaller root
        Vec3::RealType t = (-b - sqrt(delta)) / (2 * a);
        // Check if the root is in range
        if (t_min < t && t < t_max) {
            hr.t        = t;
            hr.point    = r.point_at(t);
            hr.normal   = unit_vector((hr.point - this->origin) / this->radius);
            hr.material = this->material;
        } else {
            hr.t = -1;
        }
    }
    return delta >= 0;
}

void Sphere::translate(Vec3 v) {
    // Get sphere origin
    glm::vec4 origin(this->origin.x(), this->origin.y(), this->origin.z(), 1.f);
    // Get translate factor
    glm::vec3 translate_factor(v.x(), v.y(), v.z());
    // Make translation
    glm::mat4 translate_matrix = glm::translate(glm::mat4(1.0f), translate_factor);
    glm::vec4 translation = translate_matrix * origin;
    // Move sphere
    this->origin = Point3(Vec3::RealType(translation[Vec3::X]),
                          Vec3::RealType(translation[Vec3::Y]),
                          Vec3::RealType(translation[Vec3::Z]));
}

void Sphere::rotate(Vec3 v) {
    (void) v;
}

void Sphere::scale(Vec3 v) {
    (void) v;
}

// void Sphere::transform(std::list<std::tuple<Transformation, Vec3>> ts) {
//     // Get transformations
//     Transformation t;
//     Vec3 v;
//     std::tie(t, v) = ts;
// }

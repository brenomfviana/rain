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
        if (t_max > t && t > t_min) {
            hr.t        = t;
            hr.point    = r.point_at(t);
            hr.normal   = ((hr.point - this->origin) / this->radius);
            hr.material = this->material;
            return true;
        }
        t = (-b + sqrt(delta)) / (2 * a);
        // Check if the root is in range
        if (t_max > t && t > t_min) {
            hr.t        = t;
            hr.point    = r.point_at(t);
            hr.normal   = ((hr.point - this->origin) / this->radius);
            hr.material = this->material;
            return true;
        }
    }
    return false;
}

glm::mat4 Sphere::translate(glm::vec3 v) {
    return glm::translate(glm::mat4(1.0f), v);
}

glm::mat4 Sphere::rotate(glm::vec3 v) {
    (void) v;
    return glm::mat4(1.f);
}

glm::mat4 Sphere::scale(glm::vec3 v) {
    (void) v;
    return glm::mat4(1.f);
}

void Sphere::transform(std::list<std::tuple<Transformation, Vec3>> ts) {
    // Apply transformations
    for (std::tuple<Transformation, Vec3> t : ts) {
        Transformation tn;
        Vec3 v;
        std::tie(tn, v) = t;
        // Check transformation
        if (tn == Transformation::TRANSLATE) {
            glm::mat4 translate_matrix = translate(glm::vec3(v.x(), v.y(), v.z()));
            // Get sphere origin
            glm::vec4 origin(this->origin.x(), this->origin.y(), this->origin.z(), 1.f);
            glm::vec4 translation = translate_matrix * origin;
            // Move sphere
            this->origin = Point3(Vec3::RealType(translation[Vec3::X]),
                                  Vec3::RealType(translation[Vec3::Y]),
                                  Vec3::RealType(translation[Vec3::Z]));
        } else if (tn == Transformation::SCALE) {
            // TODO
        }
    }
}

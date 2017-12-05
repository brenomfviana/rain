#include "scene/components/shape/cube.h"

Cube::Cube(Point3 origin, Point3 end) : Shape(origin) {
    this->origin = origin;
    this->end = end;
}

Cube::Cube(Point3 origin, Point3 end, Material* material) : Shape(origin, material) {
    this->origin = origin;
    this->end = end;
}

bool Cube::hit(Ray r, Vec3::RealType t_min, Vec3::RealType t_max, HitRecord& ht) {
    Vec3::RealType tmin = INFINITY, tmax = -INFINITY;
    //
    for (int i = 0; i < 3; ++i) {
        Vec3::RealType t1 = (origin[i] - r.get_origin()[i]) / r.get_direction()[i];
        Vec3::RealType t2 = (end[i] - r.get_origin()[i]) / r.get_direction()[i];
        tmin = std::max(tmin, std::min(t1, t2));
        tmax = std::min(tmax, std::max(t1, t2));
    }
    //
    if (tmax > std::max(tmin, 0.0)) {
        Vec3::RealType t = tmin;
        ht.t = tmin;
        ht.point =  r.point_at(t);
        Point3 c = (origin + end) * 0.5;
        Vec3 p = ht.point - c;
        Point3 d = (origin - end) * 0.5;
        Vec3::RealType bias = 1.000001;
        Vec3 normal = Vec3(p.x() / abs(d.x()) * bias,
                           p.y() / abs(d.y()) * bias,
                           p.z() / abs(d.z()) * bias );
        ht.normal = unit_vector(normal);
        ht.material = this->material;
        return true;
    }
    return false;
}

void Cube::expand(Cube* cube) {
    //
    Vec3::RealType xmin = std::min(cube->origin.x(), this->origin.x());
    Vec3::RealType ymin = std::min(cube->origin.y(), this->origin.y());
    Vec3::RealType zmin = std::min(cube->origin.z(), this->origin.z());
    Vec3::RealType xmax = std::max(cube->end.x(), this->end.x());
    Vec3::RealType ymax = std::max(cube->end.y(), this->end.y());
    Vec3::RealType zmax = std::max(cube->end.z(), this->end.z());
    Point3 bbox_origin = Point3(xmin, ymin, zmin);
    Point3 bbox_end = Point3(xmax, ymax, zmax);
    this->origin = bbox_origin;
    this->end = bbox_end;
}

glm::mat4 Cube::translate(glm::vec3 v) {
    return glm::translate(glm::mat4(1.f), v);
}

glm::mat4 Cube::rotate(glm::vec3 v) {
    glm::mat4 transformation = glm::mat4(1.f);
    transformation = glm::rotate(glm::mat4(1.f), v.x, glm::vec3(1.f, 0.f, 0.f)) * transformation;
    transformation = glm::rotate(glm::mat4(1.f), v.y, glm::vec3(0.f, 1.f, 0.f)) * transformation;
    transformation = glm::rotate(glm::mat4(1.f), v.z, glm::vec3(0.f, 0.f, 1.f)) * transformation;
    return transformation;
}

glm::mat4 Cube::scale(glm::vec3 v) {
    return glm::scale(glm::mat4(1.f), v);
}

void Cube::transform(std::list<std::tuple<Transformation, Vec3>> ts) {
    // Check if the list is not empty
    if (!ts.empty()) {
        // New points
        glm::vec4 new_o;
        glm::vec4 new_e;
        glm::mat4 transformations = glm::mat4(1.f);
        for (std::tuple<Transformation, Vec3> t : ts) {
            Transformation tn;
            Vec3 v;
            std::tie(tn, v) = t;
            // Check transformation
            if (tn == Transformation::TRANSLATE) {
                glm::mat4 translated_matrix = translate(glm::vec3(v.x(), v.y(), v.z()));
                transformations = translated_matrix * transformations;
            } else if (tn == Transformation::ROTATE) {
                glm::mat4 rotated_matrix = rotate(glm::vec3((v.x() * (3.141592 / 180)), (v.y() * (3.141592 / 180)), (v.z()) * (3.141592 / 180)));
                transformations = rotated_matrix * transformations;
            } else if (tn == Transformation::SCALE) {
                glm::mat4 scaled_matrix = scale(glm::vec3(v.x(), v.y(), v.z()));
                transformations = scaled_matrix * transformations;
            }
        }
        // New points
        new_o = transformations * glm::vec4(this->origin.x(), this->origin.y(), this->origin.z(), 1.f);
        new_e = transformations * glm::vec4(this->end.x(), this->end.y(), this->end.z(), 1.f);
        // Move triangle
        this->origin = Point3(Vec3::RealType(new_o[Vec3::X]),
                          Vec3::RealType(new_o[Vec3::Y]),
                          Vec3::RealType(new_o[Vec3::Z]));
        this->end = Point3(Vec3::RealType(new_e[Vec3::X]),
                          Vec3::RealType(new_e[Vec3::Y]),
                          Vec3::RealType(new_e[Vec3::Z]));
    }
}

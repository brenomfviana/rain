#include "scene/components/shape/triangle.h"

/*!
 * Triangle constructor.
 */
Triangle::Triangle(Point3 v0, Point3 v1, Point3 v2, bool back_facing_cull) : Shape(v0) {
    this->v0 = v0;
    this->v1 = v1;
    this->v2 = v2;
    this->back_facing_cull = back_facing_cull;
}

/*!
 * Triangle constructor.
 */
Triangle::Triangle(Point3 v0, Point3 v1, Point3 v2, bool back_facing_cull,
        Material* material) : Shape(v0, material) {
    this->v0 = v0;
    this->v1 = v1;
    this->v2 = v2;
    this->back_facing_cull = back_facing_cull;
}

/*!
 * Triangle destructor.
 */
Triangle::~Triangle() {
    /* empty */
}

bool Triangle::hit(Ray r, Vec3::RealType t_min, Vec3::RealType t_max, HitRecord& hr) {
    //
    Vec3::RealType t;
    Vec3::RealType u;
    Vec3::RealType v;
    //
    Vec3 tvec;
    Vec3 qvec;
    Vec3 pvec;
    // Get vector for two edges sharing v0
    Vec3 e1 = this->v1 - this->v0;
    Vec3 e2 = this->v2 - this->v0;
    // Calculates the determinant
    pvec = cross(r.get_direction(), e2);
    Vec3::RealType det = dot(e1, pvec);
    Vec3::RealType inv_det;
    // Check if the back facing cull is activated
    if (this->back_facing_cull) {
        // Check if the determinant is smaller than EPSILON
        if (det < EPSILON) {
            return false;
        }
        // Get distance from v0 to ray origin
        tvec = r.get_origin() - this->v0;
        // Calculates u parameter
        u = dot(tvec, pvec);
        // Check u parameter is within the bounds
        if ((u < 0.f) || (u > det)) {
            return false;
        }
        // Prepare to test v parameter
        qvec = cross(tvec, e1);
        v = dot(r.get_direction(), qvec);
        // Check v parameter is within the bounds
        if ((v < 0.f) || ((u + v) > det)) {
            return false;
        }
        // Calculates t parameter
        t = dot(e2, qvec);
        // Inverse determinant
        inv_det = 1.f / det;
        // Scale parameters
        t *= inv_det;
        u *= inv_det;
        v *= inv_det;
    } else {
        // Check if the determinant is between the interval (-EPSILON, EPSILON)
        if ((det > -EPSILON) && (det < EPSILON)) {
            return false;
        }
        // Inverse determinant
        inv_det = 1.f / det;
        // Get distance from v0 to ray origin
        tvec = r.get_origin() - this->v0;
        // Calculates u parameter
        u = dot(tvec, pvec) * inv_det;
        // Check u parameter is within the bounds
        if ((u < 0.f) || (u > 1.f)) {
            return false;
        }
        // Prepare to test v parameter
        qvec = cross(tvec, e1);
        v = dot(r.get_direction(), qvec) * inv_det;
        // Check v parameter is within the bounds
        if ((v < 0.f) || ((u + v) > 1.f)) {
            return false;
        }
        // Calculates t parameter
        t = dot(e2, qvec) * inv_det;
    }
    // Check if the triangle is within the limits of the scene
    if ((t > EPSILON) && ((t > t_min) && (t < t_max))) {
        hr.t        = t;
        hr.point    = r.point_at(t);
        hr.normal   = unit_vector(cross(e1, e2));
        hr.material = this->material;
        return true;
    }
    return false;
}

Point3 Triangle::get_midpoint() const {
    Vec3::RealType x = ((this->v0.x() + this->v1.x() + this->v2.x()) / 3);
    Vec3::RealType y = ((this->v0.y() + this->v1.y() + this->v2.y()) / 3);
    Vec3::RealType z = ((this->v0.z() + this->v1.z() + this->v2.z()) / 3);
    return Point3(x, y, z);
}

glm::mat4 Triangle::translate(glm::vec3 v) {
    return glm::translate(glm::mat4(1.f), v);
}

glm::mat4 Triangle::rotate(glm::vec3 v) {
    glm::mat4 transformation = glm::mat4(1.f);
    transformation = glm::rotate(glm::mat4(1.f), v.x, glm::vec3(1.f, 0.f, 0.f)) * transformation;
    transformation = glm::rotate(glm::mat4(1.f), v.y, glm::vec3(0.f, 1.f, 0.f)) * transformation;
    transformation = glm::rotate(glm::mat4(1.f), v.z, glm::vec3(0.f, 0.f, 1.f)) * transformation;
    return transformation;
}

glm::mat4 Triangle::scale(glm::vec3 v) {
    return glm::scale(glm::mat4(1.f), v);
}

void Triangle::transform(std::list<std::tuple<Transformation, Vec3>> ts) {
    // Check if the list is not empty
    if (!ts.empty()) {
        // New points
        glm::vec4 new_v0;
        glm::vec4 new_v1;
        glm::vec4 new_v2;
        // Apply transformations
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
        new_v0 = transformations * glm::vec4(this->v0.x(), this->v0.y(), this->v0.z(), 1.f);
        new_v1 = transformations * glm::vec4(this->v1.x(), this->v1.y(), this->v1.z(), 1.f);
        new_v2 = transformations * glm::vec4(this->v2.x(), this->v2.y(), this->v2.z(), 1.f);
        // Move triangle
        this->v0 = Point3(Vec3::RealType(new_v0[Vec3::X]),
                          Vec3::RealType(new_v0[Vec3::Y]),
                          Vec3::RealType(new_v0[Vec3::Z]));
        this->v1 = Point3(Vec3::RealType(new_v1[Vec3::X]),
                          Vec3::RealType(new_v1[Vec3::Y]),
                          Vec3::RealType(new_v1[Vec3::Z]));
        this->v2 = Point3(Vec3::RealType(new_v2[Vec3::X]),
                          Vec3::RealType(new_v2[Vec3::Y]),
                          Vec3::RealType(new_v2[Vec3::Z]));
    }
}

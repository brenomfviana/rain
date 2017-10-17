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

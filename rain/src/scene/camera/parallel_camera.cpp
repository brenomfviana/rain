#include "scene/camera/parallel_camera.h"

ParallelCamera::ParallelCamera(Point3 look_from, Point3 look_at, Vec3 vup,
        Vec3::RealType top, Vec3::RealType left, Vec3::RealType right,
        Vec3::RealType bottom) : Camera(look_from) {
    this->top = top;
    this->left = left;
    this->right = right;
    this->bottom = bottom;
    this->w = unit_vector(look_from - look_at);
    this->u = unit_vector(cross(vup, w));
    this->v = cross(w, u);
}

ParallelCamera::~ParallelCamera() {
    /* empty */
}

Ray ParallelCamera::get_ray(Vec3::RealType u, Vec3::RealType v) const {
    //
    u = this->left   + (this->right - this->left) * u;
    v = this->bottom + (this->top - this->bottom) * (1 - v);
    Vec3 o = this->origin + u * this->u + v * this->v;
    return Ray(o, -(this->w));
};

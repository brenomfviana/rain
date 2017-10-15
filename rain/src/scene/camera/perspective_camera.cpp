#include "scene/camera/perspective_camera.h"

PerspectiveCamera::PerspectiveCamera(Point3 look_from, Point3 look_at, Vec3 vup,
    Vec3::RealType vfov, Vec3::RealType aspect_ratio, Vec3::RealType aperture,
    Vec3::RealType fd) : Camera(look_from) {
        //
        this->lens_radius = aperture / 2;
        //
        Vec3::RealType theta = ((vfov * M_PI) / 180.f);
        Vec3::RealType half_heigth = std::tan(theta / 2);
        Vec3::RealType half_width  = aspect_ratio * half_heigth;
        //
        this->w = unit_vector(look_from - look_at);
        this->u = unit_vector(cross(vup, w));
        this->v = cross(w, u);
        // fd = (look_from - look_at).length();
        this->llc = look_from - (half_width * fd * this->u) -
                    (half_heigth * fd  * this->v) - this->w * fd;
        // Set view plane dimension
        this->horizontal = 2 * half_width  * fd * this->u;
        this->vertical   = 2 * half_heigth * fd * this->v;
}

PerspectiveCamera::~PerspectiveCamera() {
    /* empty */
}

Ray PerspectiveCamera::get_ray(Vec3::RealType u, Vec3::RealType v) const {
    Vec3 rd = this->lens_radius * random_in_unit_disk();
    Point3 p = (llc + (u * this->horizontal) + (v * this->vertical));
    Vec3 offset = (this->u * rd.x()) + (this->v * rd.y());
    return Ray(this->origin + offset, p - this->origin - offset);
};

Vec3 PerspectiveCamera::random_in_unit_disk() const {
    Vec3 p;
    do {
        p = 2.0 * Vec3(drand48(), drand48(),0 ) - Vec3(1, 1, 0);
    } while (dot(p, p) >= 1.0);
    return p;
}

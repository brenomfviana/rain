#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "shape.h"

/*!
 * This class represents a sphere.
 */
class Sphere : public Shape {

    private:
        // Sphere radius
        Vec3::RealType radius;

    public:

        /*!
         * Sphere constructor.
         *
         * @param radius Sphere radius
         * @param origin Sphere origin point
         */
        Sphere(Point3 origin, Vec3::RealType radius);

        /*!
         * Sphere constructor.
         *
         * @param radius Sphere radius
         * @param origin Sphere origin point
         * @param material Sphere material
         */
        Sphere(Point3 origin, Vec3::RealType radius, Material* material);

        /*!
         * Sphere destructor.
         */
        ~Sphere();

        bool hit(Ray r, Vec3::RealType tMin, Vec3::RealType tMax, HitRecord& hr);
};

#endif /* _SPHERE_H_ */

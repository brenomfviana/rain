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

        bool hit(Ray r, Vec3::RealType t_min, Vec3::RealType t_max, HitRecord& hr);

        void translate(Vec3 v);

        void rotate(Vec3 v);

        void scale(Vec3 v);

        // void transform(std::list<std::tuple<Transformation, Vec3>> ts);
};

#endif /* _SPHERE_H_ */

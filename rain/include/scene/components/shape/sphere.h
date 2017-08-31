#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "shape.h"

/*!
 * This class represents a sphere.
 */
class Sphere : public Shape {

    private:
        // Sphere radius
        float radius;


    public:
        /*!
         * Sphere constructor.
         *
         * @param radius_ Sphere radius
         * @param origin_ Sphere origin point
         */
        Sphere(Point3 origin_, float radius_) : Shape(origin_), radius(radius_)
            { /* empty */ }

        /*!
         * Check if the ray has hit the sphere. Returns true if the ray has hit
         * the sphere and false otherwise.
         *
         * @param r Ray
         * @param tMin
         * @param tMax
         * @param hr Hit record
         *
         * @return True if the ray has hit the sphere and false otherwise
         */
        bool hit(Ray r, float tMin, float tMax, HitRecord& hr) {
            auto oc = r.getOrigin() - origin;
            auto a = dot(r.getDirection(), r.getDirection());
            auto b = 2 * dot(oc, r.getDirection());
            auto c = dot(oc, oc) - (radius * radius);
            float delta = (b * b - 4 * a * c);
            //
            if (delta >= 0) {
                auto t = (-b - sqrt(delta)) / (2 * a);
                if (t > tMin && t < tMax) {
                    hr.t = t;
                    hr.origin = origin;
                    hr.normal = (unitVector((r.pointAt(t) - origin))
                        + Vec3(1, 1, 1)) * 0.5;
                    hr.material = material;
                } else {
                    hr.t = -1;
                }
            }
            return delta >= 0;
        }
};

#endif

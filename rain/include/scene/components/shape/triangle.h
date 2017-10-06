#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include "shape.h"

/*!
 * This class represents a triangle.
 */
class Triangle : public Shape {

    private:
        // Vertices
        Point3 u;
        Point3 v;
        Point3 v2;
        Vec3 normal;

    public:

        /*!
         * Triangle constructor.
         *
         * @param origin Triangle origin
         * @param v0 First vertex of the triangle
         * @param v1 Second vertex of the triangle
         * @param v2 Third vertex of the triangle
         */
        Triangle(Point3 origin, Point3 v0, Point3 v1, Point3 v2) :
            Shape(origin), u(v0 - v1), v(v1 - v2) {
            normal = unitVector(cross(u, v));
        }

        /*!
         * Triangle constructor.
         *
         * @param origin Triangle origin
         * @param v0 First vertex of the triangle
         * @param v1 Second vertex of the triangle
         * @param v2 Third vertex of the triangle
         * @param material Triangle material
         */
        Triangle(Point3 origin, Point3 v0, Point3 v1, Point3 v2,
                Material* material) :
                Shape(origin, material), u(v0 - v1), v(v1 - v2) {
                normal = unitVector(cross(u, v));
        }

        bool hit(Ray r, float tMin, float tMax, HitRecord& hr) {
            float d = dot(r.getDirection(), normal);
            // Parallel
            if (d == 0) {
                return false;
            }
            //
            auto t = dot(origin - r.getOrigin(), normal) / d;
            // Check if the root is in range
            if (tMin < t && t < tMax) {
                hr.t = t;
                hr.point = r.pointAt(t);
                hr.normal = (d > 0 ? -normal : normal);
                hr.material = material;
                return true;
            } else {
                hr.t = -1;
                return false;
            }
        }
};

#endif /* _TRIANGLE_H_ */

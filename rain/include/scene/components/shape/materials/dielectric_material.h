#ifndef _DIELECTRIC_MATERIAL_H_
#define _DIELECTRIC_MATERIAL_H_

#include <cmath>
#include "material.h"

using namespace utils;

/*!
 * This class represents a metal material.
 */
class DielectricMaterial : public Material {

    public:
        //
        Vec3::RealType ri;

        /*!
         * Dielectric material constructor.
         *
         * @param ri
         */
        DielectricMaterial(Vec3::RealType ri) : ri(ri) { /* empty */ }

        /*!
         * .
         */
        float schlick(float cosine, float ri) const {
            float r = (1.f - ri) / (1.f + ri);
            r = r * r;
            return (r + (1.f - r) * std::pow((1.f - cosine), 5.f));
        }

        /*!
         * Get refracted ray direction.
         *
         * @param v Incoming ray direction
         * @param n Normal vector
         *
         * @return If the ray was refracted
         */
        bool refract(const Vec3& v, const Vec3& n, float niOVERnt,
                Vec3& refracted) const {
            //
            float dt = dot(unitVector(v), n);
            //
            float discriminant = 1.f - (niOVERnt * niOVERnt * (1.f - dt * dt));
            //
            if (discriminant > 0) {
                refracted = niOVERnt * (v - n * dt) - n * std::sqrt(discriminant);
                return true;
            } else {
                return false;
            }
        }

        /*!
         * Get reflected ray direction.
         *
         * @param v Incoming ray direction
         * @param n Normal vector
         *
         * @return Reflected ray direction
         */
        Vec3 reflect(const Vec3& v, const Vec3& n) const {
            return v - 2 * dot(v, n) * n;
        }

        bool scatter(const Ray& r, const HitRecord& hr, RGB& attenuation,
                Ray& sray) const {
            //
            Vec3 outwardNormal;
            //
            Vec3 reflected = reflect(r.getDirection(), hr.normal);
            //
            float niOVERnt;
            //
            attenuation = Vec3(1.f, 1.f, 1.f);
            //
            float reflectProb;
            float cosine;
            //
            float d = dot(r.getDirection(), hr.normal);
            if (d > 0) {
                outwardNormal = -hr.normal;
                niOVERnt = ri;
                cosine = ri * d / r.getDirection().length();
            } else {
                outwardNormal = hr.normal;
                niOVERnt = 1.f / ri;
                cosine = - d / r.getDirection().length();
            }
            //
            Vec3 refracted;
            //
            if (refract(r.getDirection(), outwardNormal, niOVERnt, refracted)) {
                reflectProb = schlick(cosine, ri);
            } else {
                sray = Ray(hr.point, reflected);
                reflectProb = 1.f;
            }
            //
            if (drand48() < reflectProb) {
                sray = Ray(hr.point, reflected);
            } else {
                sray = Ray(hr.point, refracted);
            }
			return true;
        }
};

#endif /* _METAL_MATERIAL_H_ */

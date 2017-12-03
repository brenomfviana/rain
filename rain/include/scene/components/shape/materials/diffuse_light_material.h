#ifndef _DIFFUSE_LIGHT_MATERIAL_H_
#define _DIFFUSE_LIGHT_MATERIAL_H_

#include "material.h"
#include "texture.h"

using namespace utils;

/*!
 * This class represents the diffuse light material.
 */
class DiffuseLightMaterial : public Material {

    private:
        // Light color
        RGB emit;

    public:
        /*!
         * Diffuse light material constructor.
         *
         * @param emit Light color
         */
        DiffuseLightMaterial(RGB emit);

        /*!
         * Diffuse light material destructor.
         */
        ~DiffuseLightMaterial();

        bool scatter(const Ray& r, const HitRecord& hr, RGB& attenuation,
                Ray& sray) const;

        Vec3 emitted(Vec3::RealType u, Vec3::RealType v, const Vec3& p) const;
};

#endif /* _DIFFUSE_LIGHT_MATERIAL_H_ */

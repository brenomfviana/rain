#ifndef _CONSTANT_TEXTURE_H_
#define _CONSTANT_TEXTURE_H_

#include "vec3.h"
#include "ray.h"
#include "texture.h"

using namespace utils;

/*!
 * This class represents a constant texture.
 */
class ConstantTexture : public Texture {

    private:
        // Color
        RGB color;

    public:

        /*!
         * Constant texture constructor.
         */
        ConstantTexture();

        /*!
         * Constant texture constructor.
         *
         * @param color Color
         */
        ConstantTexture(RGB color);

        /*!
         * Constant texture destructor.
         */
        ~ConstantTexture();

    	RGB value(Vec3::RealType u, Vec3::RealType v, const Vec3& p) const;
};

#endif /* _CONSTANT_TEXTURE_H_ */

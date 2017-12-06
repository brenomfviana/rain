#ifndef _PERLIN_TEXTURE_H_
#define _PERLIN_TEXTURE_H_

#include "vec3.h"
#include "ray.h"
#include "texture.h"
#include "perlin.h"

using namespace utils;

/*!
 * This class represents the perlin noise texture.
 */
class PerlinTexture : public Texture {

    private:
        // Perlin noise
        Perlin noise;
        // Scale
        Vec3::RealType scale;

    public:

        /*!
         * Perlin texture constructor.
         */
        PerlinTexture();

        /*!
         * Perlin texture constructor.
         *
         * @param color Color
         */
        PerlinTexture(Vec3::RealType scale);

        /*!
         * Perlin texture destructor.
         */
        ~PerlinTexture();

    	RGB value(Vec3::RealType u, Vec3::RealType v, const Vec3& p) const;
};

#endif /* _PERLIN_TEXTURE_H_ */

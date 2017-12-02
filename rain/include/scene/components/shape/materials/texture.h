#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "vec3.h"
#include "ray.h"

/*!
 * This class represents a texture.
 */
class Texture {

    public:
        /*!
         * .
         *
         * @param u
         * @param v
         * @param p
         */
    	virtual RGB value(Vec3::RealType u, Vec3::RealType v, const Vec3& p) const = 0;
};

#include "constant_texture.h"
#include "checker_texture.h"

#endif /* _TEXTURE_H_ */

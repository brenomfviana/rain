#ifndef _CHECKER_TEXTURE_H_
#define _CHECKER_TEXTURE_H_

#include "vec3.h"
#include "ray.h"
#include "texture.h"

using namespace utils;

/*!
 * This class represents a checker texture.
 */
class CheckerTexture : public Texture {

    private:
        // Odd
        Texture* odd;
        // Even
        Texture* even;

    public:

        /*!
         * Checker texture constructor.
         */
        CheckerTexture();

        /*!
         * Checker texture constructor.
         *
         * @param odd Odd
         * @param even Even
         */
        CheckerTexture(Texture* odd, Texture* even);

        /*!
         * Constant texture destructor.
         */
        ~CheckerTexture();

    	RGB value(Vec3::RealType u, Vec3::RealType v, const Vec3& p) const;
};

#endif /* _CHECKER_TEXTURE_H_ */

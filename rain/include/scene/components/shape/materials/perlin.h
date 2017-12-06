#ifndef _PERLIN_H_
#define _PERLIN_H_

#include "vec3.h"

using namespace utils;

class Perlin {

    public:

        static Vec3 *ranvec;
        static int *perm_x;
        static int *perm_y;
        static int *perm_z;

        /*!
         * TODO.
         */
        Vec3::RealType noise(const Vec3& p) const;

        /*!
         * TODO.
         */
        Vec3::RealType turb(const Vec3& p, int depth = 7) const;

        /*!
         * TODO.
         */
        static Vec3* perlin_generate();

        /*!
         * TODO.
         */
        static void permute(int *p, int n);

        /*!
         * TODO.
         */
        static int* perlin_generate_perm();
};

#endif /* _PERLIN_H_ */

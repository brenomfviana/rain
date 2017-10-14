#ifndef _DEPTH_MAP_SHADER_H_
#define _DEPTH_MAP_SHADER_H_

#include "shader.h"

using namespace utils;

/*!
 * This class respresents the Depth Map shader.
 */
class DepthMapShader : public Shader {

    private:
        // Max depth
        Vec3::RealType max_depth;
        // Scene foreground
        RGB foreground;
        // Scene background
        RGB background;

    public:
        /*!
         * Depth Map shader constructor.
         *
         * @param max_depth Max depth
         * @param foreground Scene foreground
         * @param background Scene background
         */
        DepthMapShader(Vec3::RealType max_depth, RGB foreground, RGB background);

        /*!
         * Depth Map shader destructor.
         */
        ~DepthMapShader();

        RGB color(const Ray& r, const Scene& scene, int nrays) const;
};

#endif /* _DEPTH_MAP_SHADER_H_ */

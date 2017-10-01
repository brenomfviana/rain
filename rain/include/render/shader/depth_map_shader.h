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
        float maxDepth;
        // Scene foreground
        RGB foreground;
        // Scene background
        RGB background;

    public:
        /*!
         * Depth Map shader constructor.
         *
         * @param maxDepth_ Max depth
         * @param foreground_ Scene foreground
         * @param background_ Scene background
         */
        DepthMapShader(float maxDepth_, RGB foreground_, RGB background_) :
            maxDepth(maxDepth_), foreground(foreground_), background(background_)
            { /* empty */ }

        RGB color(const Ray& r, const Scene& scene, int nrays) const {
            (void) (nrays);
            // Check hit
            HitRecord hr;
            if (intersect(r, scene, hr)) {
                // Check depth
                if (hr.t >= 0 && hr.t <= maxDepth) {
                    float t = hr.t / maxDepth;
                    return (foreground * (1 - t)) + (background * t);
                }
            }
            return background;
        }
};

#endif /* _DEPTH_MAP_SHADER_H_ */

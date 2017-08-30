#ifndef _DEPTH_MAP_SHADER_H_
#define _DEPTH_MAP_SHADER_H_

#include "shader.h"
#include "utils/vec3.h"

/*!
 * This class respresents a depth map shader.
 */
class DepthMapShader : public Shader {

    private:
        // Max depth
        float maxDepth;
        //
        RGB foreground;
        //
        RGB background;

    public:
        /*!
         * .
         */
        DepthMapShader(float maxDepth_, RGB foreground_, RGB background_) :
            maxDepth(maxDepth_), foreground(foreground_), background(background_)
            { /* empty */ }

        /*!
         * .
         */
        RGB color(const Ray& r, Scene& scene, int nrays) const {
            // Check hit
            HitRecord hr;
            if (intersect(r, scene, hr)) {
                if (hr.t >= 0 && hr.t <= maxDepth) {
                    float t = hr.t / maxDepth;
                    return (foreground * (1 - t)) + (background * t);
                }
            }
            return background;
        }
};

#endif

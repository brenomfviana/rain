#ifndef _RAY_TRACER_H_
#define _RAY_TRACER_H_

#include <cmath>
#include <iostream>
#include <memory>
#include <random>
#include <thread>
#include <vector>
#include "ray.h"
#include "image.h"
#include "scene/camera/camera.h"
#include "scene/components/hit_record.h"
#include "shader/shader.h"
#include "progress_bar.h"

using namespace utils;

/*!
 * This is the ray tracer, is the class is responsible for all rendering.
 */
class RayTracer {

    public:
        /*!
         * Render an image using ray tracing technique.
         *
         * @param cam Camera
         * @param scene Scene
         * @param shader Shader
         * @param width Image width
         * @param height Image height
         * @param nsamples Number of samples for anti-aliasing
         * @param nrays Number of rays of the recursion
         *
         * @return Rendered image
         */
        static Image* render(Camera* cam, Scene& scene, Shader* shader,
                unsigned int width, unsigned int height, unsigned int nsamples,
                unsigned int nrays);

    private:
        /*!
         * Render an image using ray tracing technique.
         *
         * @param img Image to render
         * @param cam Camera
         * @param scene Scene
         * @param shader Shader
         * @param width Image width
         * @param height Image height
         * @param nsamples Number of samples for anti-aliasing
         * @param nrays Number of rays of the recursion
         */
        static void raytrace(Image* img, Camera* cam, Scene& scene, Shader* shader,
                int width, int height_top, int height_bottom, unsigned int nsamples,
                unsigned int nrays, ProgressBar* p);
};

#endif /* _RAY_TRACER_H_ */

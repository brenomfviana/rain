#ifndef _RAY_TRACE_H_
#define _RAY_TRACE_H_

#include <cmath>
#include <iostream>
#include <memory>
#include <random>
#include <thread>
#include <vector>
#include "ray.h"
#include "shader/shader.h"
#include "scene/components/hit_record.h"
#include "utils/progress_bar.h"

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
        static Image* render(Camera& cam, Scene& scene, Shader* shader,
                unsigned int width, unsigned int height, unsigned int nsamples,
                unsigned int nrays) {
            // Create image
            Image* img = new Image(width, height);
            std::vector<std::thread*> ts;
            // Progress bar
            ProgressBar* p = new ProgressBar(70, width * height);
            // Y axis
            for (unsigned int row = 0, i = (img->height - 1); row < img->height;
                    row++, i--) {
                // Create a thread for each image line
                std::thread* t = new std::thread(xAxis, img, row, i, std::ref(cam),
                    std::ref(scene), shader, nsamples, nrays, p);
                ts.push_back(t);
    		}
            // Wait all threads
            for (std::thread* t : ts) {
                t->join();
            }
            return img;
        }

    private:
        /*!
         * Render an image line.
         *
         * @param img
         * @param cam Camera
         * @param scene Scene
         * @param shader Shader
         * @param width Image width
         * @param height Image height
         * @param nsamples Number of samples for anti-aliasing
         * @param nrays Number of rays of the recursion
         * @param p Progress bar
         */
        static void xAxis(Image* img, unsigned int row, unsigned int i,
                Camera& cam, Scene& scene, Shader* shader, unsigned int nsamples,
                int nrays, ProgressBar* p) {
            // Seed to generate random numbers
            std::mt19937 gen(1);
            // X axis
            for(unsigned int col = 0; col < img->width; col++) {
                // Pixel color
                RGB c(0, 0, 0);
                // Antialiasing
                for(unsigned int ns = 0; ns < nsamples; ns++) {
                    // Walked v% of the vertical dimension of the view plane
                    float v = float(row + std::generate_canonical<double, 10>(gen)) / float(img->height);
                    // Walked u% of the horizontal dimension of the view plane
                    float u = float(col + std::generate_canonical<double, 10>(gen)) / float(img->width);
                    Point3 endPoint = cam.llc + (u * cam.horizontal) +
                        (v * cam.vertical);
                    // The ray
                    Ray r(cam.origin, endPoint - cam.origin);
                    c += shader->color(r, scene, nrays);
                }
                c /= float(nsamples);
                // Check shader
                if (typeid(*shader) == typeid(BlinnPhongShader) ||
                    typeid(*shader) == typeid(LambertianShader)) {
                    // Gamma correction
                    c = RGB(sqrt(c[RGB::X]), sqrt(c[RGB::Y]), sqrt(c[RGB::Z]));
                }
                // Convert color formart
                int ir = int(255.99f * c[RGB::R]);
                int ig = int(255.99f * c[RGB::G]);
                int ib = int(255.99f * c[RGB::B]);
                // Print the pixel in the image
                img->pixels[(i * img->width * 3) + (col * 3)] = ir;
                img->pixels[(i * img->width * 3) + (col * 3) + 1] = ig;
                img->pixels[(i * img->width * 3) + (col * 3) + 2] = ib;
                p->increase();
            }
        }
};

#endif /* _RAY_TRACE_H_ */

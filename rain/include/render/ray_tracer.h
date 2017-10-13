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
                unsigned int nrays) {
            // Create image
            Image* img = new Image(width, height);
            // Progress bar
            ProgressBar* p = new ProgressBar(70, width * height);
            int n_ts = 4;
            std::vector<std::thread> ts(n_ts);
            int n = 1;
            while (n <= n_ts) {
				int height_top = (height * (n * 1.f / n_ts)) - 1;
				int height_bottom = height * ((n - 1) * 1.0 / n_ts);
				ts[n - 1] = std::thread(raytracer, img, cam, std::ref(scene), shader,
                    width, height_top, height_bottom, nsamples, nrays, p);
		    	n++;
			}
            // Wait all threads
            for (std::thread& t : ts) {
                t.join();
            }
            return img;
        }

    private:
        static void raytracer(Image* img, Camera* cam, Scene& scene, Shader* shader,
                int width, int height_top, int height_bottom, unsigned int nsamples,
                unsigned int nrays, ProgressBar* p) {
            // Y axis
            for (int row = height_top; row >= height_bottom; --row) {
                // Create a thread for each image line
                // Seed to generate random numbers
                std::mt19937 gen(1);
                // X axis
                for(int col = 0; col < img->width; col++) {
                    // Pixel color
                    RGB c(0, 0, 0);
                    // Antialiasing
                    for(unsigned int ns = 0; ns < nsamples; ns++) {
                        // Walked v% of the vertical dimension of the view plane
                        float v = float(row + std::generate_canonical<double, 10>(gen)) / float(img->height);
                        // Walked u% of the horizontal dimension of the view plane
                        float u = float(col + std::generate_canonical<double, 10>(gen)) / float(img->width);
                        Ray r = cam->getRay(u, v);
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
                    img->pixels[((img->height - row - 1) * img->width * 3) + (col * 3)]     = ir;
                    img->pixels[((img->height - row - 1) * img->width * 3) + (col * 3) + 1] = ig;
                    img->pixels[((img->height - row - 1) * img->width * 3) + (col * 3) + 2] = ib;
                    p->increase();
                }
    		}
        }
};

#endif /* _RAY_TRACE_H_ */

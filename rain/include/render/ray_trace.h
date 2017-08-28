#ifndef _RAY_TRACE_H_
#define _RAY_TRACE_H_

#include <random>
#include <iostream>
#include "render/ray.h"

class RayTrace {

    public:
        /*!
         * Render an image using ray tracing technique.
         *
         * @param cam Camera
         * @param scene Scene
         * @param width Image width
         * @param height Image height
         * @param nsmaples
         *
         * @return Rendered image
         */
        static Image* render(Camera& cam, Scene& scene, unsigned int width,
            unsigned int height, unsigned int nsamples) {
            // Create image
            Image* img = new Image(width, height);
            // Seed to generate random numbers
            std::mt19937 gen(1);
            int nrays = 10;
            // Y axis
            for (unsigned int row = 0, i = (img->height - 1); row < img->height;
                row++, i--) {
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
                        c += color(r, scene, nrays);
                    }
                    c /= float(nsamples);
    				// Convert color formart
    				int ir = int(255.99f * c[RGB::R]);
    				int ig = int(255.99f * c[RGB::G]);
    				int ib = int(255.99f * c[RGB::B]);
                    // Print the pixel in the image
                    img->pixels[(i * img->width * 3) + (col * 3)] = ir;
                    img->pixels[(i * img->width * 3) + (col * 3) + 1] = ig;
                    img->pixels[(i * img->width * 3) + (col * 3) + 2] = ib;
    			}
    		}
            return img;
        }

    private:
        /*!
        * Get the color of the reached pixel.
        *
        * @param r Ray
        * @param scene Scene
        *
        * @return The color of the reached pixel
        */
        static RGB color(const Ray& r, Scene scene, int nrays) {
            // Check hit
            float tMin = 0;
            float tMax = 10;
            Vec3 o;
            float t = std::numeric_limits<float>::infinity();
            Vec3 normal;
            //
            for (auto &shape : scene.components) {
                //
                HitRecord hr;
                //
                if (shape->hit(r, tMin, tMax, hr)) {
                    //
                    if (hr.t > -1 && t > hr.t) {
                        t = hr.t;
                        o = hr.origin;
                        normal = hr.normal;
                    }
                }
            }
            //
            if (t > 0 && t < std::numeric_limits<float>::infinity()) {
                //
                if (nrays-- <= 0) {
                    return normal;
                }
                return 0.5 * color(r, scene, nrays);
            }
            // Get background corners colors
            RGB ul = scene.background.upperLeft;
            RGB ll = scene.background.lowerLeft;
            RGB ur = scene.background.upperRight;
            RGB lr = scene.background.lowerRight;
            // Bilinear interpolation
            auto rd = r.getDirection();
            auto w = (rd.x() * 0.25) + 0.5;
            auto x = (rd.y() * 0.5) + 0.5;
            return ((ll * (1 - x) * (1 - w)) + (ul * x * (1 - w)) +
            (lr * (1 - x) * w) + (ur * x *w));
        }
};

#endif

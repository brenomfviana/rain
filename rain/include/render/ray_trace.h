#ifndef _RAY_TRACE_H_
#define _RAY_TRACE_H_

#include <random>
#include <thread>
#include <vector>
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
            int nrays = 10;
            std::vector<std::thread*> ts;
            // Y axis
            for (unsigned int row = 0, i = (img->height - 1); row < img->height;
                row++, i--) {
                std::thread* t = new std::thread(xAxis, img, row, i, std::ref(cam), std::ref(scene), nsamples, nrays);
                ts.push_back(t);
    		}
            //
            for (std::thread* t : ts) {
                t->join();
            }
            return img;
        }

    private:
        /*!
         * .
         */
        static void xAxis(Image* img, unsigned int row, unsigned int i, Camera& cam, Scene& scene,
            int nsamples, int nrays) {
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
            HitRecord hr;
            if (intersect(r, scene, hr)) {
                //
                if (nrays-- <= 0) {
                    return RGB(1, 0, 0);
                }
                return 0.5 * Vec3(1, 1, 1) * color(r, scene, nrays);
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

        /*!
         * .
         */
        static bool intersect(const Ray& r, Scene scene, HitRecord& hr) {
            // Check hit
            float tMin = 0;
            float tMax = 10;
            //
            hr.t = std::numeric_limits<float>::infinity();
            //
            for (auto &shape : scene.components) {
                //
                HitRecord haux;
                //
                if (shape->hit(r, tMin, tMax, haux)) {
                    //
                    if (haux.t > -1 && hr.t > haux.t) {
                        hr.t = haux.t;
                        hr.origin = haux.origin;
                        hr.normal = haux.normal;
                    }
                }
            }
            return (hr.t > 0 && hr.t < std::numeric_limits<float>::infinity());
        }
};

#endif

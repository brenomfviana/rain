#ifndef _RAY_TRACE_H_
#define _RAY_TRACE_H_

#include <random>
#include <iostream>
#include "render/ray.h"

class RayTrace {

    public:
        /*!
         * .
         */
        static Image* render(Camera& cam, Scene& scene, unsigned int width,
                unsigned int height, unsigned int nsamples) {
            Image* img = new Image(width, height);

            std::mt19937 gen(1);

            // Y
            for (unsigned int row = 0, i = (img->height - 1); row < img->height;
                row++, i--) {
                // X
    		   	for(unsigned int col = 0; col < img->width; col++) {
    				//
                    RGB c(0, 0, 0);

                    for(unsigned int ns = 0; ns < nsamples; ns++) {
                        // Walked v% of the vertical dimension of the view plane
                        float v = float(row + std::generate_canonical<double, 10>(gen)) / float(img->height);
        				// Walked u% of the horizontal dimension of the view plane
        				float u = float(col + std::generate_canonical<double, 10>(gen)) / float(img->width);
        				Point3 endPoint = cam.llc + (u * cam.horizontal) +
                            (v * cam.vertical);
                        // The ray
                        Ray r(cam.origin, endPoint - cam.origin);
                        c += color(r, scene);
                    }

                    c /= float(nsamples);
    				//
    				int ir = int(255.99f * c[RGB::R]);
    				int ig = int(255.99f * c[RGB::G]);
    				int ib = int(255.99f * c[RGB::B]);
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
        static RGB color(const Ray& r, Scene scene) {
            // Check hit
            float tMin = 0;
            float tMax = 10;
            float t = std::numeric_limits<float>::infinity();
            Vec3 o;
            for (auto &shape : scene.components) {
                //
                HitRecord hr;
                if (shape->hit(r, tMin, tMax, hr)) {
                    if (hr.t > -1 && t > hr.t) {
                        t = hr.t;
                        o = hr.origin;
                    }
                }
            }

            if (t > 0 && t < std::numeric_limits<float>::infinity()) {
                Vec3 normal = unitVector((r.pointAt(t) - o));
                auto N = (normal + Vec3(1, 1, 1)) * 0.5;
                return N;
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

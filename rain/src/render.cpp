#include <iostream>
#include <limits>
#include <cmath>
#include "utils/vec3.h"
#include "render/ray.h"
#include "image/image.h"
#include "scene/scene_reader.h"
#include "printer/printer.h"


struct Sphere {
    Point3 center;
    float radius;
};

Sphere s[4] = {{Point3(0, -100.5, -3), 99.f},
               {Point3(0.3,    0, -1),  0.4},
               {Point3(0,      1, -2),  0.6},
               {Point3(-0.4,   0, -3),  0.7}};

/*!
 * .
 */
float hitSphere(const Ray& r, const Point3 center, float radius) {
    auto oc = r.getOrigin() - center;
    auto A = dot(r.getDirection(), r.getDirection());
    auto B = 2 * dot(oc, r.getDirection());
    auto C = dot(oc, oc) - (radius * radius);
    float delta = (B * B - 4 * A * C);
    //
    if (delta >= 0) {
       auto t = (-B - sqrt(delta)) / (2 * A);
       // auto t2 = (-B + sqrt(delta)) / (2 * A);
       return t;
    }
    return -1;
}

/*!
 * Get the color of the reached pixel.
 *
 * @return The color of the reached pixel
 */
RGB color(const Ray& r, RGB depth_foreground, RGB depth_background, float depth) {
    Point3 center;
    float t = std::numeric_limits<float>::infinity();
    for (int i = 0; i < 4; i++) {
        float aux = hitSphere(r, s[i].center, s[i].radius);
        if (aux > -1 && t > aux) {
            t = aux;
            center = s[i].center;
        }
    }

    if (t > 0 && t < std::numeric_limits<float>::infinity()) {
        if (t >= 0 && t <= depth) {
            t = t / depth;
            return (depth_foreground * (1 - t)) + depth_background * t;
        } else {
            return depth_background;
        }
    }
    return depth_background;
}

int main(int argc, char *argv[]) {
	// Check for a valid number of arguments
	if (argc != 2) {
		// ERROR
		std::cout << "Error: Invalid number of arguments!" << std::endl;
	} else {
        Scene scene;
        Image img;
		// Read file
        SceneReader::read(argv[1], scene, img);
		// Create camera
		// Lower left corner of the view plane
		Point3 llc(-2, -1, -1);
		// Horizontal dimension of the view plane
	    Vec3 horizontal(4, 0, 0);
		// Vertical dimension of the view plane
	    Vec3 vertical(0, 2, 0);
		// The camera's origin
	    Point3 origin(0, 0, 0);

        float depth = 3;
        // Black -> White
        RGB depth_foreground = RGB(0, 0, 0);
        RGB depth_background = RGB(1, 1, 1);
        // White -> Black
        // RGB depth_foreground = RGB(1, 1, 1);
        // RGB depth_background = RGB(0, 0, 0);
		// Print image
	   	for (unsigned int row = 0, i = (img.height - 1); row < img.height; row++, i--) {   // Y
            // Walked v% of the vertical dimension of the view plane
            float v = float(row) / float(img.height);
		   	for(unsigned int col = 0; col < img.width; col++) { // X
				// Walked u% of the horizontal dimension of the view plane
				float u = float(col) / float(img.width);
				Point3 endPoint = llc + (u * horizontal) + (v * vertical);
				// The ray
				Ray r(origin, endPoint - origin);
				auto c = color(r, depth_foreground, depth_background, depth);
				// Print pixel
				int ir = int(255.99f * c[RGB::R]);
				int ig = int(255.99f * c[RGB::G]);
				int ib = int(255.99f * c[RGB::B]);
                img.pixels[(i * img.width * 3) + (col * 3)] = ir;
                img.pixels[(i * img.width * 3) + (col * 3) + 1] = ig;
                img.pixels[(i * img.width * 3) + (col * 3) + 2] = ib;
			}
		}
        // Print image
        Printer::print(img, "");
	}
    return 0;
}

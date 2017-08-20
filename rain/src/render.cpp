#include <iostream>
#include "utils/vec3.h"
#include "render/ray.h"
#include "image/image.h"
#include "render/io/printer.h"
#include "render/io/scene_reader.h"
#include "scene/components/shape/sphere.h"

/*!
 * Get the color of the reached pixel.
 *
 * @param r Ray
 * @param scene Scene
 *
 * @return The color of the reached pixel
 */
RGB color(const Ray& r, Scene scene) {
	// Get background corners colors
    RGB ul = scene.background.upperLeft;
	RGB ll = scene.background.lowerLeft;
	RGB ur = scene.background.upperRight;
	RGB lr = scene.background.lowerRight;

    // Check hit
    for (auto &shape : scene.components) {
        //
        if (shape->hit(r, 0, 0)) {
            return RGB(1, 1, 0);
        }
    }

    // Bilinear interpolation
    auto rd = r.getDirection();
    auto w = (rd.x() * 0.25) + 0.5;
    auto t = (rd.y() * 0.5) + 0.5;
    return ((ll * (1 - t) * (1 - w)) + (ul * t * (1 - w)) +
			(lr * (1 - t) * w) + (ur * t *w));
}

int main(int argc, char *argv[]) {
	// Check for a valid number of arguments
	if (argc != 2) {
		// ERROR
		std::cout << "Error: Invalid number of arguments!" << std::endl;
	} else {
        Scene scene;
        OutputSettings os;
		// Read file
        SceneReader::read(argv[1], scene, os);

        Image img(os.width, os.height);

        //
        Shape* s = new Sphere(Point3(0, 0, -5), 1);
        scene.addShape(s);

		// Create camera
		// Lower left corner of the view plane
		Point3 llc(-2, -1, -1);
		// Horizontal dimension of the view plane
	    Vec3 horizontal(4, 0, 0);
		// Vertical dimension of the view plane
	    Vec3 vertical(0, 2, 0);
		// The camera's origin
	    Point3 origin(0, 0, 0);

		// Print image
        // Y
	   	for (unsigned int row = 0, i = (img.height - 1); row < img.height; row++, i--) {
            // Walked v% of the vertical dimension of the view plane
            float v = float(row) / float(img.height);
            // X
		   	for(unsigned int col = 0; col < img.width; col++) {
				// Walked u% of the horizontal dimension of the view plane
				float u = float(col) / float(img.width);
				Point3 endPoint = llc + (u * horizontal) + (v * vertical);
				// The ray
				Ray r(origin, endPoint - origin);
				auto c = color(r, scene);
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
        Printer::print(img, os, "");
	}
    return 0;
}

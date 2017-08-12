#include <iostream>
#include <fstream>
#include "utils/vec3.h"
#include "render/ray.h"
#include "image/image.h"
#include "scene/scene_reader.h"

/**
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
		// Read file
		Scene scene = SceneReader::read(argv[1]);
		// Create image
		Image img(scene.width, scene.height, scene.name,
                  scene.type, scene.codification);
		// Create camera
		// Lower left corner of the view plane.
		Point3 lower_left_corner(-2, -1, -1);
		// Horizontal dimension of the view plane.
	    Vec3 horizontal(4, 0, 0);
		// Vertical dimension of the view plane.
	    Vec3 vertical(0, 2, 0);
		// The camera's origin.
	    Point3 origin(0, 0, 0);

		// Print image
	   	for (int row = (scene.height - 1); row >= 0; --row) {     // Y
		   	for(unsigned int col = 0; col < scene.width; col++) { // X
				// Walked u% of the horizontal dimension of the view plane
				float u = float(col) / float(img.width);
				// Walked v% of the vertical dimension of the view plane
				float v = float(row) / float(img.height);
				Point3 end_point = lower_left_corner + (u * horizontal) + (v * vertical);
				// The ray
				Ray r(origin, end_point - origin);
				auto c = color(r, scene);
				// Print pixel
				int ir = int(255.99f * c[RGB::R]);
				int ig = int(255.99f * c[RGB::G]);
				int ib = int(255.99f * c[RGB::B]);
                img.pixels[(row * img.width * 3) + (col * 3)] = ir;
                img.pixels[(row * img.width * 3) + (col * 3) + 1] = ig;
                img.pixels[(row * img.width * 3) + (col * 3) + 2] = ib;
			}
		}

        std::ofstream outfile(scene.name, std::ofstream::binary);

    	outfile << "P6" << std::endl;
    	outfile << img.width << " " << img.height << std::endl;
    	outfile << "255" << std::endl;

    	outfile.write(img.pixels, img.width * img.height * 3);
      	outfile.close();
	}
    return 0;
}

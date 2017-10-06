#include <ctime>
#include <fstream>
#include <iostream>
#include "utils/image.h"
#include "scene/scene.h"
#include "scene/camera.h"
#include "render/ray_tracer.h"
#include "render/io/printer.h"
#include "render/shader/shader.h"
#include "render/io/scene_reader.h"

using namespace utils;

int main(int argc, char *argv[]) {
	// Check if the number of arguments is valid
	if (argc != 2) {
		// Print error
		std::cerr << "\033[1;31mError: Invalid number of arguments!\033[0m\n";
	} else {
		try {
			// Scene
	        Scene scene;
	        Camera cam;
			Shader* shader;
			// Ray tracer settings
			int samples;
			int nrays;
			// Output settings
			OutputSettings os;
			std::cout << "Opening scene description file...\n";
			// Read scene description file
        	SceneReader::read(argv[1], scene, cam, shader, os, samples, nrays);
			std::cout << "\033[1;34mScene description file "
					  << "opened successfully!\033[0m\n";

			// TEST AREA
			PointLight* pl = new PointLight(Point3(0, -1, 0), Vec3(1, 1, 1));
			scene.addLight(pl);
			/*DirectionalLight* l = new DirectionalLight(Point3(20, 10, 5), Vec3(1, 1, 1));
			scene.addLight(l);*/
			// END TEST AREA

			// Start rendering
			std::cout << "Starts to rendering...\n";
			// Get start time
			time_t start = time(0);
			// Render
	        Image img = *(RayTracer::render(cam, scene, shader, os.width,
				os.height, samples, nrays));
			// Get end time
			time_t end = time(0);
			// Print render time
			std::cout << "\033[1;34m\nThe image was rendered in "
					  << difftime(end, start) << " seconds.\033[0m\n";
  	        // Print image
			std::cout << "Printing image...\n";
	        Printer::print(img, os, "");
			std::cout << "\033[1;34mThe image was printed successfully.\033[0m\n";
		} catch (const char* e) {
			// Print error
			std::cerr << "\033[1;31m" << e << "\033[0m\n";
		}
	}
    return EXIT_SUCCESS;
}

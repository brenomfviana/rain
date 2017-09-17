#include <fstream>
#include <iostream>
#include <ctime>
#include "utils/image.h"
#include "scene/scene.h"
#include "scene/camera.h"
#include "scene/components/shape/sphere.h"
#include "render/ray_tracer.h"
#include "render/io/printer.h"
#include "render/io/scene_reader.h"
#include "render/shader/shader.h"

using namespace utils;

int main(int argc, char *argv[]) {
	// Check for a valid number of arguments
	if (argc != 2) {
		// ERROR
		std::cout << "\033[1;31mError: Invalid number of arguments!\033[0m\n";
	} else {
		try {
			// Scene description
	        Scene scene;
	        Camera cam;
			Shader* shader;
			// Ray tracer settings
			int samples;
			int nrays;
			// Output settings
			OutputSettings os;
			std::cout << "Opening scene description file...\n";
			// Read file
        	SceneReader::read(argv[1], scene, cam, shader, os, samples, nrays);
			std::cout << "\033[1;34mScene description file "
					  << "opened successfully!\033[0m\n";
			std::cout << "Starts to rendering...\n";
			// Start time
			time_t start = time(0);
			// Render
	        Image img = *(RayTracer::render(cam, scene, shader, os.width,
				os.height, samples, nrays));
			// End time
			time_t end = time(0);
			// Print render time
			std::cout << "\033[1;34m\nThe image was rendered in "
					  << difftime(end, start) << " seconds.\033[0m\n";
			std::cout << "Printing image...\n";
	        // Print image
	        Printer::print(img, os, "");
			std::cout << "\033[1;34mThe image was printed successfully.\033[0m\n";
		} catch (const char* e) {
			std::cout << "\033[1;31m" << e << "\033[0m\n";
		}
	}
    return EXIT_SUCCESS;
}

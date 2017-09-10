#include <iostream>
#include <fstream>
#include "image/image.h"
#include "scene/scene.h"
#include "scene/camera.h"
#include "scene/components/shape/sphere.h"
#include "render/ray_tracer.h"
#include "render/io/printer.h"
#include "render/io/scene_reader.h"
#include "render/shader/shader.h"

int main(int argc, char *argv[]) {
	// Check for a valid number of arguments
	if (argc != 2) {
		// ERROR
		std::cout << "\033[1;31mError: Invalid number of arguments!\033[0m\n";
	} else {
		try {
	        Scene scene;
			OutputSettings os;
			Shader* shader;
	        Camera cam;
			// Read file
        	SceneReader::read(argv[1], scene, cam, shader, os);
			// Render
	        Image img = *(RayTracer::render(cam, scene, shader, os.width,
				 							os.height, 10));
	        // Print image
	        Printer::print(img, os, "");
		} catch (const char* e) {
			std::cout << "\033[1;31m" << e << "\033[0m\n";
		}
	}
    return 0;
}

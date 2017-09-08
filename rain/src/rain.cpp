#include <iostream>
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
		std::cout << "Error: Invalid number of arguments!" << std::endl;
	} else {
		// TODO: Check if the file exists
        Scene scene;
		OutputSettings os;
		Shader* shader;
        Camera cam;
		// Read file
        SceneReader::read(argv[1], scene, cam, shader, os);
		// TODO: Check shader

        // Render
        Image img = *(RayTracer::render(cam, scene, shader, os.width, os.height,
			 							10));
        // Print image
        Printer::print(img, os, "");
	}
    return 0;
}

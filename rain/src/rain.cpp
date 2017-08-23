#include <iostream>
#include "image/image.h"
#include "scene/scene.h"
#include "scene/camera.h"
#include "render/ray_trace.h"
#include "render/io/printer.h"
#include "render/io/scene_reader.h"

int main(int argc, char *argv[]) {
	// Check for a valid number of arguments
	if (argc != 2) {
		// ERROR
		std::cout << "Error: Invalid number of arguments!" << std::endl;
	} else {
        Scene scene;
        Camera cam;
        OutputSettings os;
		// Read file
        SceneReader::read(argv[1], scene, cam, os);
        // Render
        Image img = *(RayTrace::render(cam, scene, os.width, os.height, 10));
        // Print image
        Printer::print(img, os, "");
	}
    return 0;
}

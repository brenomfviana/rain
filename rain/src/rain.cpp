#include <iostream>
#include "image/image.h"
#include "scene/scene.h"
#include "scene/camera.h"
#include "scene/components/shape/sphere.h"
#include "render/ray_trace.h"
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
        Camera cam;
        OutputSettings os;
		// Read file
        SceneReader::read(argv[1], scene, cam, os);
		// TODO: Check shader
		Shader* shader = new BlinnPhongShader();
		Sphere* s = new Sphere(Point3(0, 0, -1), 0.4);
		s->material = Material(Vec3(0, 1, 0), Vec3(0.3, 0.3, 0.3), Vec3(1, 1, 1), 10);
		scene.addShape(s);
        // Render
        Image img = *(RayTrace::render(cam, scene, shader, os.width, os.height, 10));
        // Print image
        Printer::print(img, os, "");
	}
    return 0;
}

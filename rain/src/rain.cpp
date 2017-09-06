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
        Camera cam;
        OutputSettings os;
		// Read file
        SceneReader::read(argv[1], scene, cam, os);
		// TODO: Check shader

		//
		Shader* shader = new BlinnPhongShader();
		// Scene description
		// Ambient light
		scene.alight = Light(Vec3(0.f, 0.f, 0.f), Vec3(0.4, 0.4, 0.4));
		// S1
		Sphere* s1 = new Sphere(Point3(0, -100.5, -1), 100.f);
		s1->material = Material(Vec3(0.4, 0.4, 0.4), Vec3(1, 1, 1), 5.f, Vec3(0.1, 0.1, 0.1));
		scene.addShape(s1);
		// S2
		Sphere* s2 = new Sphere(Point3(0, 0, -1), 0.4);
		s2->material = Material(Vec3(0.f, 0.3, 0.8), Vec3(0.9, 0.9, 0.9), 64.f, Vec3(0.1, 0.1, 0.1));
		scene.addShape(s2);

		Light* l = new Light(Vec3(20, 10, 5), Vec3(1.f, 1.f, 1.f));
		scene.addLight(l);

        // Render
        Image img = *(RayTracer::render(cam, scene, shader, os.width, os.height, 10));
        // Print image
        Printer::print(img, os, "");
	}
    return 0;
}

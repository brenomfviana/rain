#include <iostream>
#include "../utility/vec3.h"
#include "../utility/ray.h"

/*
 * In the near future we'll want to refactor our project to become something
 * like the code below.
 */
#ifdef TRADITIONAL_RT
Image Raytrace (Camera cam, Scene scene, int width, int height) {
	Image image = new Image (width, height) ;
	for (int i = 0 ; i < height ; i++) {
		for (int j = 0 ; j < width ; j++) {
			Ray ray = RayThruPixel (cam, i, j) ;
			Intersection hit = Intersect (ray, scene) ;
			image[i][j] = FindColor (hit) ;
		}
    }
	return image ;
}
#endif

RGB color(const Ray& r_) {
    RGB bottom(0.5, 0.7, 0);
    RGB top(1, 1, 1);
    // TODO: determine the background color, which is an linear interpolation between bottom->top.
    // The interpolation is based on where the ray hits the background.
    // Imagine that the background is attached to the view-plane; in other words,
    // the virtual world we want to visualize is empty!
    return top; // Stub, replace it accordingly
}

int main(int argc, char *argv[]) {
    int n_cols{ 200 };
    int n_rows{ 100 };
    std::cout << "P3\n"
              << n_cols << " " << n_rows << "\n"
              << "255\n";
    //=== Defining our 'camera'
    Point3 lower_left_corner(-2, -1, -1); // lower left corner of the view plane.
    Vec3 horizontal(4, 0, 0); // Horizontal dimension of the view plane.
    Vec3 vertical(0, 2, 0); // Vertical dimension of the view plane.
    Point3 origin(0, 0, 0); // the camera's origin.
     // NOTICE: We loop rows from bottom to top.
    for (int row{n_rows-1} ; row >= 0 ; --row) { // Y
        for(int col{0} ; col < n_cols ; col++) { // X
            // Determine how much we have 'walked' on the image: in [0,1]
            float u = float(col) / float(n_cols); // walked u% of the horizontal dimension of the view plane.
            float v = float(row) / float(n_rows); // walked v% of the vertical dimension of the view plane.
            // Determine the ray's direction, based on the pixel coordinate (col,row).
            // We are mapping (matching) the view plane (vp) to the image.
            // To create a ray we need: (a) an origin, and (b) an end point.
            //
            // (a) The ray's origin is the origin of the camera frame (which is the same as the world's frame).
            //
            // (b) To get the end point of ray we just have to 'walk' from the
            // vp's origin + horizontal displacement (proportional to 'col') +
            // vertical displacement (proportional to 'row').
            Point3 end_point = lower_left_corner + u * horizontal + v * vertical;
            // The ray:
            Ray r(origin, end_point - origin);
            // Determine the color of the ray, as it travels through the virtual space.
            auto c = color(r);
            int ir = int(255.99f * c[RGB::R]);
            int ig = int(255.99f * c[RGB::G]);
            int ib = int(255.99f * c[RGB::B]);
            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }
    return 0;
}

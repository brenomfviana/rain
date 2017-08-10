#include <iostream>
#include "../utility/vec3.h"
#include "../utility/ray.h"

using namespace utility;

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

bool hitSphere(const Ray& r, const Point3 c, float radius) {
    auto oc = r.getOrigin() - c;
    auto A = dot(r.getDirection(), r.getDirection());
    auto B = 2 * dot(oc, r.getDirection());
    auto C = dot(oc, oc) - (radius * radius);
    return (B * B - 4 * A * C) >= 0;
}

RGB color(const Ray& r) {
    RGB top(0.5, 0.7, 1);
    RGB bottom(1, 1, 1);
    if (hitSphere(r, Vec3(0, 0, -5), 0.8)) {
        return RGB(1, 0, 0);
    }
    // 
    auto unitRay = unitVector(r.getDirection());
    auto y = unitRay.y();
    auto t = (y + 1) * 0.5;
    return (bottom * (1 - t) + top * (t));
}

int main(int argc, char *argv[]) {
    int n_cols{ 1024 };
    int n_rows{ 1024 };
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
            Point3 end_point = lower_left_corner + (u * horizontal) + (v * vertical);
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

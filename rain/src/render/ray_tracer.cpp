#include "render/ray_tracer.h"

Image* RayTracer::render(Camera* cam, Scene& scene, Shader* shader,
        unsigned int width, unsigned int height, unsigned int nsamples,
        unsigned int nrays) {
    // Create image
    Image* img = new Image(width, height);
    // Progress bar
    ProgressBar* p = new ProgressBar(70, width * height);
    int n_ts = 4;
    std::vector<std::thread> ts(n_ts);
    int n = 1;
    while (n <= n_ts) {
        int height_top = (height * (n * 1.f / n_ts)) - 1;
        int height_bottom = height * ((n - 1) * 1.0 / n_ts);
        ts[n - 1] = std::thread(raytrace, img, cam, std::ref(scene), shader,
            width, height_top, height_bottom, nsamples, nrays, p);
        n++;
    }
    // Wait all threads
    for (std::thread& t : ts) {
        t.join();
    }
    return img;
}

void RayTracer::raytrace(Image* img, Camera* cam, Scene& scene, Shader* shader,
        int width, int height_top, int height_bottom, unsigned int nsamples,
        unsigned int nrays, ProgressBar* p) {
    // Y axis
    for (int row = height_top; row >= height_bottom; --row) {
        // Create a thread for each image line
        // Seed to generate random numbers
        std::mt19937 gen(1);
        // X axis
        for(int col = 0; col < width; col++) {
            // Pixel color
            RGB c;
            // Antialiasing
            for(unsigned int ns = 0; ns < nsamples; ns++) {
                // Walked v% of the vertical dimension of the view plane
                Vec3::RealType v = Vec3::RealType(row + std::generate_canonical<double, 10>(gen)) / Vec3::RealType(img->height);
                // Walked u% of the horizontal dimension of the view plane
                Vec3::RealType u = Vec3::RealType(col + std::generate_canonical<double, 10>(gen)) / Vec3::RealType(img->width);
                Ray r = cam->get_ray(u, v);
                c += shader->color(r, scene, nrays);
            }
            c /= Vec3::RealType(nsamples);
            // Check shader
            if (typeid(*shader) == typeid(BlinnPhongShader) ||
                typeid(*shader) == typeid(LambertianShader)) {
                // Gamma correction
                c = RGB(sqrt(c[RGB::X]), sqrt(c[RGB::Y]), sqrt(c[RGB::Z]));
            }
            // Convert color formart
            int ir = int(255.99f * c[RGB::R]);
            int ig = int(255.99f * c[RGB::G]);
            int ib = int(255.99f * c[RGB::B]);
            // Print the pixel in the image
            img->pixels[((img->height - row - 1) * img->width * 3) + (col * 3)]     = ir;
            img->pixels[((img->height - row - 1) * img->width * 3) + (col * 3) + 1] = ig;
            img->pixels[((img->height - row - 1) * img->width * 3) + (col * 3) + 2] = ib;
            p->increase();
        }
    }
}

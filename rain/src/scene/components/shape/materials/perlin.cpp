#include "scene/components/shape/materials/perlin.h"

Vec3 *Perlin::ranvec = perlin_generate();
int *Perlin::perm_x = perlin_generate_perm();
int *Perlin::perm_y = perlin_generate_perm();
int *Perlin::perm_z = perlin_generate_perm();

Vec3::RealType perlin_interp(Vec3 c[2][2][2], Vec3::RealType u, Vec3::RealType v, Vec3::RealType w) {
    Vec3::RealType uu = u * u * (3 - 2 * u);
    Vec3::RealType vv = v * v * (3 - 2 * v);
    Vec3::RealType ww = w * w * (3 - 2 * w);
    Vec3::RealType accum = 0;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                Vec3 weight_v = Vec3(u - i, v - j, w - k);
                accum += (i * uu + (1 - i) * (1 - uu))* (j * vv + (1 - j) * (1 - vv)) *
                    (k * ww + (1 - k) * (1 - ww)) * dot(c[i][j][k], weight_v);
            }
        }
    }
    return accum;
}

Vec3::RealType Perlin::noise(const Vec3& p) const {
    Vec3::RealType u = p.x() - floor(p.x());
    Vec3::RealType v = p.y() - floor(p.y());
    Vec3::RealType w = p.z() - floor(p.z());
    int i = floor(p.x());
    int j = floor(p.y());
    int k = floor(p.z());
    Vec3 c[2][2][2];
    for (int di = 0; di < 2; di++) {
        for (int dj = 0; dj < 2; dj++) {
            for (int dk = 0; dk < 2; dk++) {
                c[di][dj][dk] = ranvec[perm_x[(i+di) & 255] ^
                                perm_y[(j+dj) & 255] ^
                                perm_z[(k+dk) & 255]];
            }
        }
    }
    return perlin_interp(c, u, v, w);
}

Vec3::RealType Perlin::turb(const Vec3& p, int depth) const {
    Vec3::RealType accum = 0;
    Vec3 temp_p = p;
    Vec3::RealType weight = 1.0;
    for (int i = 0; i < depth; i++) {
        accum += (weight * noise(temp_p));
        weight *= 0.5;
        temp_p *= 2;
    }
    return fabs(accum);
}

Vec3* Perlin::perlin_generate() {
    Vec3 * p = new Vec3[256];
    for (int i = 0; i < 256; i++) {
        p[i] = unit_vector(Vec3(-1 + 2 * drand48(),
                                -1 + 2 * drand48(),
                                -1 + 2 * drand48()));
    }
    return p;
}

void Perlin::permute(int *p, int n) {
    for (int i = n - 1; i > 0; i--) {
        int target = int(drand48() * (i + 1));
        int tmp = p[i];
        p[i] = p[target];
        p[target] = tmp;
    }
}

int* Perlin::perlin_generate_perm() {
    int* p = new int[256];
    for (int i = 0; i < 256; i++) {
        p[i] = i;
    }
    permute(p, 256);
    return p;
}

#ifndef _CEL_SHADER_H_
#define _CEL_SHADER_H_

#include "shader.h"
#include "scene/components/light/light.h"

using namespace utils;

#define PI 3.14159265

/*!
 * This class represents the Blinn-Phong shader.
 */
class CelShader : public Shader {

    private:
        // Border color
        RGB borderColor;

    public:
        /*!
         * Cel shader constructor.
         *
         * @param borderColor Border color
         */
        CelShader(RGB borderColor) : borderColor(borderColor) { /* empty */ }

        RGB color(const Ray& r, const Scene& scene, int nrays) const {
            (void) nrays;
            // Check hit
            HitRecord hr;
            if (intersect(r, scene, hr)) {
                // Check if is a border
                float borderAngle = dot(unitVector(-r.getDirection()), hr.normal) /
                    ((-r.getDirection()).length() * hr.normal.length());
                if (borderAngle < 0.1736) {
                    return borderColor;
                }
                // Get Cel material
                CelMaterial* material = dynamic_cast<CelMaterial*>(hr.material);
                RGB c;
                // Color shape
                HitRecord shr;
                for (auto& light : scene.lights) {
                    if (!intersect(Ray(hr.point, light->getDirection()), scene,
                            shr)) {
                        // Check angle and get correspondent color
                        Vec3 l = light->getDirection() - r.getDirection();
                        float angle = dot(shr.normal, l) /
                            (hr.normal.length() * l.length());
                        // for (int i = material->angles.size() - 1; i > 0; i--) {
                        for (int i = 0; i < material->angles.size(); i++) {
                            if (angle >= material->angles[i]) {
                                c += material->colors[i];
                                break;
                            }
                        }
                    }
                }
                return c;
            } else {
                return background(r, scene);
            }
        }
};

#endif /* _CEL_SHADER_H_ */

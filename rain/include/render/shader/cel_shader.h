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
                float a = material->angles.size() - 1;
                for (auto& light : scene.lights) {
                    // Check angle and get correspondent color
                    Vec3 l = light->getDirection(hr.point) - r.getDirection();
                    float angle = dot(hr.normal, l) /
                        (hr.normal.length() * l.length());
                    for (size_t i = 0; i < material->angles.size(); i++) {
                        if (angle >= material->angles[i] && a >= i) {
                            a = i;
                            c = material->colors[i];
                            break;
                        }
                    }
                }
                return (c / scene.lights.size());
            } else {
                return background(r, scene);
            }
        }
};

#endif /* _CEL_SHADER_H_ */

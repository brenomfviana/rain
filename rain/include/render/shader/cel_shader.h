#ifndef _CEL_SHADER_H_
#define _CEL_SHADER_H_

#include "shader.h"
#include "scene/components/light/light.h"

using namespace utils;

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
            if (intersect(r, scene, 0, 10, hr)) {
                // Check if is a border
                float borderAngle = dot(unitVector(-r.getDirection()), hr.normal) /
                    ((-r.getDirection()).length() * hr.normal.length());
                if (borderAngle < 0.1736) {
                    return borderColor;
                }
                // Get Cel material
                CelMaterial* material = dynamic_cast<CelMaterial*>(hr.material);
                RGB c;
                // Lighting
                HitRecord shr;
                float pickedAngle = material->angles.size();
                bool shadow = false;
                int n_shadows = 1;
                for (auto& light : scene.lights) {
                    // Check shadow
                    if (!intersect(Ray(hr.point, unitVector(light->getDirection(hr.point))),
                            scene, 0, 10, shr)) {
                        // Check angle and get correspondent color
                        Vec3 l = light->getDirection(hr.point) - r.getDirection();
                        float angle = dot(hr.normal, l) / (hr.normal.length() * l.length());
                        // 
                        for (int i = material->angles.size() - 1; i >= 0; i--) {
                            if ((i == 0 && angle >= material->angles[i] && pickedAngle > i) ||
                                    (angle <= material->angles[i - 1] &&
                                     angle >= material->angles[i] && pickedAngle > i)) {
                                pickedAngle = i;
                                c = material->colors[i];
                            }
                        }
                    } else {
                        shadow = true;
                        n_shadows++;
                    }
                }
                if (shadow) {
                    return (c / (scene.lights.size() * n_shadows));
                } else {
                    return (c / scene.lights.size());
                }
            } else {
                return background(r, scene);
            }
        }
};

#endif /* _CEL_SHADER_H_ */

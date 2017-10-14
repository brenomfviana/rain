#ifndef _SCENE_H_
#define _SCENE_H_

#include <list>
#include "components/background.h"
#include "components/light/light.h"
#include "components/shape/shape.h"

/*!
 * This class represents a scene.
 */
class Scene {

    public:
        // Scene background
        Background background;
        // Scene lights
        std::list<Light*> lights;
        // Scene components
        std::list<Shape*> components;

        /*!
         * Empty scene.
         */
        Scene() {
            /* empty */
        }

        /*!
         * Scene constructor.
         *
         * @param background Scene background
         */
        Scene(Background background) {
            this->background = background;
        }

        /*!
         * Scene destructor.
         */
        ~Scene() {
            /* empty */
        }

        /*!
         * Add a shape to the scene.
         *
         * @param shape Shape to be added to the scene
         */
        inline void add_shape(Shape* shape) {
            components.push_back(shape);
        }

        /*!
         * Add a light to the scene.
         *
         * @param light Light to be added to the scene
         */
        inline void add_light(Light* light) {
            lights.push_back(light);
        }
};

#endif /* _SCENE_H_ */

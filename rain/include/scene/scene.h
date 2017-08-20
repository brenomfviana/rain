#ifndef _SCENE_H_
#define _SCENE_H_

#include <list>
#include "components/background.h"
#include "components/shape/shape.h"

/*!
 * This class represents a scene.
 */
class Scene {

    public:
        // Scene background
        Background background;
        // Scene components
        std::list<Shape*> components;

        /*!
         * Empty scene.
         */
        Scene() { /* empty */ }

        /*!
         * Scene constructor.
         *
         * @param background_ Scene background
         */
        Scene(Background background_) : background(background_) { /* empty */ }

        /*!
         * Add a shape to the scene.
         *
         * @param shape Shape to be added to the scene
         */
        void addShape(Shape* shape) {
            components.push_back(shape);
        }
};

#endif

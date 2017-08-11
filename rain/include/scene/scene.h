#ifndef _SCENE_H_
#define _SCENE_H_

#include <string>
#include "vec3.h"
#include "components/background.h"

/*!
 * This class represents a scene.
 */
class Scene {

    public:
        // Image name
        std::string name;
        // Image type
        std::string type;
        // Image codification
        std::string codification;
        // Image width
        unsigned int width;
        // Image height
        unsigned int height;
        // Scene background
        Background background;
        // Scene components

        /*!
         * Scene constructor.
         *
         * @param name_ Image name
         * @param type_ Image type
         * @param codification_ Image codification
         * @param width_ Image width
         * @param height_ Image height
         * @param background_ Scene background
         */
        Scene(std::string name_, std::string type_, std::string codification_,
            unsigned int width_, unsigned int height_, Background background_) :
            name(name_), type(type_), codification(codification_), width(width_),
            height(height_), background(background_)
            { /* empty */ }

        /*!
         * Empty scene.
         */
        Scene() { /* empty */ }
};

#endif

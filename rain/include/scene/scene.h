#ifndef _SCENE_H_
#define _SCENE_H_

#include <string>
#include "utils/vec3.h"
#include "components/background.h"
#include "image/image_file_formats.h"

/*!
 * This class represents a scene.
 */
class Scene {

    public:
        // Image name
        std::string name;
        // Image type
        ImageFileFormats type;
        // Image codification
        Codifications codification;
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
        Scene(std::string name_, ImageFileFormats type_, Codifications codification_,
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

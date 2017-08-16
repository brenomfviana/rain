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
        // Scene background
        Background background;
        // Scene components

        /*!
         * Scene constructor.
         *
         * @param background_ Scene background
         */
        Scene(Background background_) : background(background_) { /* empty */ }

        /*!
         * Empty scene.
         */
        Scene() { /* empty */ }
};

#endif

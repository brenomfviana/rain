#ifndef _SCENE_READER_H_
#define _SCENE_READER_H_

#include <list>
#include <string>
#include <vector>
#include <fstream>
#include "utils/vec3.h"
#include "scene/scene.h"
#include "output_settings.h"

/*!
 * This class is responsible for reading the scene.
 */
class SceneReader {

    public:
        /*!
         * Read a scene.
         *
         * @param path Scene file path
         * @param scene Scene to be readed
         * @param os Output settings
         *
         * @return Readed scene
         */
        static void read(const std::string path, Scene& scene, OutputSettings& os);

    private:
        /*!
         * Interpret output settings of the scene file.
         *
         * @param lines File lines
         *
         * @return Output settings
         */
        static OutputSettings* interpretOutputSettings(std::list<std::string>& lines);

        /*!
         * Interpret the scene file.
         *
         * @param lines File lines
         *
         * @return Interpreted scene
         */
        static Scene* interpretScene(std::list<std::string>& lines);

        /*!
         * Split a string and return the RGB corresponding to this string.
         *
         * @param str String to be splited
         *
         * @return A RGB value
         */
        static RGB getRGB(std::string str);
};

#endif

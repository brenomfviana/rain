#ifndef _SCENE_READER_H_
#define _SCENE_READER_H_

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include "utils/vec3.h"
#include "scene.h"
#include "image/image_file_formats.h"
#include "components/background.h"

/*!
 * This class is responsible for reading the scene.
 */
class SceneReader {

    public:
        /*!
         * Read a scene.
         *
         * @param path Scene file path
         *
         * @return Readed scene
         */
        static Scene read(const std::string path);

    private:
        /*!
         * Split a string and get the RGB corresponding to this string.
         *
         * @param str String to be splited
         *
         * @return The RGB corresponding to this string
         */
        static RGB splitRGB(std::string str);

        /*!
         * Interpret the scene file.
         *
         * @param lines File lines
         *
         * @return Interpreted scene
         */
        static Scene interpretFile(std::list<std::string> lines);
};

#endif

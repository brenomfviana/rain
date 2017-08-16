#ifndef _SCENE_READER_H_
#define _SCENE_READER_H_

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include "utils/vec3.h"
#include "scene.h"
#include "image/image.h"
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
        static void read(const std::string path, Scene& scene, Image& img);

    private:
        /*!
         * Split a string and get the RGB corresponding to this string.
         *
         * @param str String to be splited
         *
         * @return A RGB value
         */
        static RGB getRGB(std::string str);

        /*!
         * Interpret header of the scene file.
         *
         * @param lines File lines
         *
         * @return Interpreted image
         */
        static Image* interpretImage(std::list<std::string>& lines);

        /*!
         * Interpret the scene file.
         *
         * @param lines File lines
         *
         * @return Interpreted scene
         */
        static Scene* interpretScene(std::list<std::string>& lines);
};

#endif

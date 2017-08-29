#ifndef _SCENE_READER_H_
#define _SCENE_READER_H_

#include <list>
#include <string>
#include <vector>
#include <fstream>
#include "utils/vec3.h"
#include "utils/split.h"
#include "scene/scene.h"
#include "scene/camera.h"
#include "output_settings.h"
#include "scene/components/shape/shape.h"
#include "scene/components/shape/sphere.h"

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
         * @param camera Camera
         * @param os Output settings
         *
         * @return Readed scene
         */
        static void read(const std::string path, Scene& scene, Camera& cam,
            OutputSettings& os) {
            // Open scene file
            std::ifstream file(path.c_str());
            // Check if the file exists
            if (!file) {
                // ERROR
                throw "Error: The file is not exists.";
            } else
                // Check if the file is open
                if (!file.is_open()) {
                // ERROR
                throw "Error: The file could not be opened.";
            } else {
                std::list<std::string> lines;
                // Read all lines of file and removes useless chars
                std::string line;
                while (getline(file, line)) {
                    // Remove indentation
                    while (line.find("    ") == 0) {
                        line = line.replace(line.find("    "), 4, "");
                    }
                    // Remove comments
                    unsigned int i = line.find("#");
                    if (i < line.length()) {
                        std::string aux;
                        if (i == 0) {
                            aux = line.replace(i, line.length(), "");
                        } else {
                            aux = line.replace(i, line.length() - 1, "");
                        }
                        if (aux.length() > 0) {
                            line = aux;
                        } else {
                            continue;
                        }
                    }
                    // Adds in list
                    lines.push_back(line);
                }
                // Close file
                file.close();
                // Interprets file
                os = *(interpretOutputSettings(lines));
                cam = *(interpretCamera(lines));
                scene = *(interpretScene(lines));
            }
        }

    private:
        #include "scene_reader.inl"
};

#endif

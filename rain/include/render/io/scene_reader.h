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
#include "render/shader/shader.h"
#include "scene/components/light.h"
#include "scene/components/background.h"
#include "scene/components/shape/shape.h"
#include "scene/components/shape/sphere.h"
#include "scene/components/shape/materials/material.h"

/*!
 * This class is responsible for reading the scene description.
 */
class SceneReader {

    public:
        /*!
         * Read a scene description.
         *
         * @param path Scene file path
         * @param scene Scene to be readed
         * @param cam Scene camera
         * @param shader Shader
         * @param os Output settings
         */
        static void read(const std::string path, Scene& scene, Camera& cam,
                         Shader*& shader, OutputSettings& os) {
            // Open scene file
            std::ifstream file(path.c_str());
            // Check if the file exists
            if (!file) {
                // ERROR
                throw "Error: The file is not exists!";
            } else
                // Check if the file is open
                if (!file.is_open()) {
                    // ERROR
                    throw "Error: The file could not be opened!";
                } else {
                    // Get file lines
                    std::list<std::string> lines;
                    getFormattedLines(lines, file);
                    // Close file
                    file.close();
                    // Interprets file
                    os     = *(interpretOutputSettings(lines));
                    cam    = *(interpretCamera(lines));
                    shader =   interpretShader(lines);
                    // Check shader
                    if (typeid(*shader) == typeid(BackgroundShader) ||
                        typeid(*shader) == typeid(Normals2RGBShader) ||
                        typeid(*shader) == typeid(DepthMapShader)) {
                        scene  = *(interpretScene(lines, false));
                    } else if (typeid(*shader) == typeid(BlinnPhongShader*)) {
                        scene  = *(interpretScene(lines, true));
                    } else {
                        throw "ERROR";
                    }
                }
        }

    private:
        /*!
         * Clears all useless content from the scene description file.
         *
         * @param lines Get file lines already formatted
         * @param file Readed file
         */
        static void getFormattedLines(std::list<std::string>& lines,
                                      std::ifstream& file) {
            // Read all lines of file and removes useless chars
            lines.clear();
            std::string line;
            while (getline(file, line)) {
                // Remove indentation
                while (line.find(" ") == 0) {
                    line = line.replace(line.find(" "), 1, "");
                }
                // Remove comments
                unsigned int i = line.find("#");
                if (i < line.length()) {
                    std::string aux;
                    // Check if the entire line is a comment
                    if (i == 0) {
                        aux = line.replace(i, line.length(), "");
                    } else {
                        aux = line.replace(i, line.length() - 1, "");
                    }
                    // Check if the line is not empty
                    if (aux.length() > 0) {
                        line = aux;
                    } else {
                        continue;
                    }
                }
                // Adds in list
                lines.push_back(line);
            }
        }

        /*!
         * Interpret output settings of the scene file.
         *
         * @param lines File lines
         *
         * @return Output settings
         */
        static OutputSettings* interpretOutputSettings(std::list<std::string>& lines) {
            // Format size
            int fsize = 5;
            // Scene format
            std::string format[] = {"NAME: ", "TYPE: ", "CODIFICATION: ",
                               "WIDTH: ", "HEIGHT: "};
            // Interpret file
            std::list<std::string>::iterator itr = lines.begin();
            std::list<std::string>::iterator begin = lines.begin();
            // Check format
            for (int i = 0; i < fsize; i++) {
                if ((*itr).find(format[i]) == 0) {
                    std::string aux = *(itr++);
                    format[i] = aux.replace(0, format[i].length(), "");
                } else {
                    // ERROR
                    throw "Invalid file format!";
                }
            }
            // Remove interpreted lines
            lines.erase(begin, itr);
            // Create image
            OutputSettings* os = new OutputSettings(std::stoi(format[3]),
                std::stoi(format[4]), format[0],
                OutputSettings::getImageFileFormat(format[1]),
                OutputSettings::getCodification(format[2]));
            return os;
        }

        /*!
         * Interpret scene camera.
         *
         * @param lines File lines
         *
         * @return Readed camera
         */
        static Camera* interpretCamera(std::list<std::string>& lines) {
            // Format size
            int fsize = 4;
            // Camara format
            std::string format[] = {"LLC: ", "H: ", "V: ", "O: "};
            // Interpret file
            std::list<std::string>::iterator itr = lines.begin();
            std::list<std::string>::iterator begin = lines.begin();
            // Look for other scene components
            if (!lines.empty() && (*(itr++)).find("CAMERA:") == 0) {
                // Check format
                for (int i = 0; i < fsize; i++) {
                    if ((*itr).find(format[i]) == 0) {
                        std::string aux = *(itr++);
                        format[i] = aux.replace(0, format[i].length(), "");
                    } else {
                        // ERROR
                        throw "Invalid file format in camera description!";
                    }
                }
                // Remove interpreted lines
                lines.erase(begin, itr);
                Camera* cam = new Camera(getVec3(format[0]), getVec3(format[1]),
                    getVec3(format[2]), getVec3(format[3]));
                return cam;
            } else {
                // ERROR
                throw "Invalid file format! Needs the camera description.";
            }
        }

        /*!
         * Interpret shader.
         *
         * @param lines File lines
         *
         * @return Readed shader
         */
        static Shader* interpretShader(std::list<std::string>& lines) {
            // Interpret file
            std::list<std::string>::iterator itr = lines.begin();
            std::list<std::string>::iterator begin = lines.begin();
            // Look for other scene components
            if (!lines.empty() && (*(itr++)).find("SHADER:") == 0) {
                std::string aux = *(itr++);
                // Remove interpreted lines
                lines.erase(begin, itr);
                if (aux.find("BACKGROUND") == 0) {
                    return (new BackgroundShader());
                } else if (aux.find("NORMALS2RGB") == 0) {
                    return (new Normals2RGBShader());
                } else if (aux.find("DEPTHMAP") == 0) {
                    return getDephtMapShader(lines);
                } else if (aux.find("BLINNPHONG") == 0) {
                    return getBlinnPhongShader(lines);
                } else {
                    throw "Invalid shader!";
                }
            } else {
                // ERROR
                throw "Invalid file format! Needs the shader description.";
            }
        }

        /*!
         * .
         *
         * @param lines File lines
         *
         * @return .
         */
        static DepthMapShader* getDephtMapShader(std::list<std::string>& lines) {
            // Depht map format
            int fsize = 3;
            std::string format[] = {"DEPTH:", "FOREGROUND:", "BACKGROUND:"};
            // Interpret file
            std::list<std::string>::iterator itr = lines.begin();
            std::list<std::string>::iterator begin = lines.begin();
            for (int i = 0; i < fsize; i++) {
                // Check format
                if ((*itr).find(format[i]) == 0) {
                    std::string aux = *(itr++);
                    format[i] = aux.replace(0, format[i].length(), "");
                } else {
                    // ERROR
                    throw "Invalid file!";
                }
            }
            // Remove interpreted lines
            lines.erase(begin, itr);
            return (new DepthMapShader(atof(format[0].c_str()),
                                       getRGB(format[1]),
                                       getRGB(format[2])));
        }

        /*!
         * .
         *
         * @param lines File lines
         *
         * @return .
         */
        static BlinnPhongShader* getBlinnPhongShader(std::list<std::string>& lines) {
            // Depht map format
            int fsize = 1;
            std::string format[] = {"AMBIENT_LIGHT: "};
            // Interpret file
            std::list<std::string>::iterator itr = lines.begin();
            std::list<std::string>::iterator begin = lines.begin();
            for (int i = 0; i < fsize; i++) {
                // Check format
                if ((*itr).find(format[i]) == 0) {
                    std::string aux = *(itr++);
                    format[i] = aux.replace(0, format[i].length(), "");
                } else {
                    // ERROR
                    throw "Invalid file!";
                }
            }
            // Remove interpreted lines
            lines.erase(begin, itr);
            return (new BlinnPhongShader(getRGB(format[0])));
        }

        // Scene reader
        #include "scene_reader.inl"
};

#endif

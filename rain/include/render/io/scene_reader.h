#ifndef _SCENE_READER_H_
#define _SCENE_READER_H_

#include <algorithm>
#include <cmath>
#include <fstream>
#include <list>
#include <string>
#include <vector>
#include "output_settings.h"
#include "render/shader/shader.h"
#include "scene/scene.h"
#include "scene/camera/camera.h"
#include "scene/components/light/light.h"
#include "scene/components/background.h"
#include "scene/components/shape/shape.h"
#include "scene/components/shape/sphere.h"
#include "scene/components/shape/materials/material.h"
#include "vec3.h"
#include "split.h"

using namespace utils;

/*!
 * This class is responsible for reading the scene description.
 */
class SceneReader {

    public:
        /*!
         * Read a scene description and return the results through the
         * referenced parameters.
         *
         * @param path Scene file path
         * @param scene Scene to be readed
         * @param cam Scene camera
         * @param shader Shader
         * @param os Output settings
         * @param samples Number of samples for anti-aliasing
         * @param nrays Number of rays of the recursion
         */
        inline static void read(const std::string path, Scene& scene, Camera*& cam,
                Shader*& shader, OutputSettings& os, int& samples, int& nrays) {
            // Open scene file
            std::ifstream file(path.c_str());
            // Check if the file exists
            if (!file) {
                // ERROR
                throw "Error:The file is not exists!";
            } else
                // Check if the file is open
                if (!file.is_open()) {
                    // ERROR
                    throw "Error:The file could not be opened!";
                } else {
                    // Get file lines
                    std::list<std::string> lines;
                    getFormattedLines(lines, file);
                    // Close file
                    file.close();
                    // Interprets file
                    os = *(interpretOS(lines));
                    interpretRTSettings(lines, samples, nrays);
                    cam = interpretCamera(lines);
                    shader = interpretShader(lines);
                    // Check shader
                    if (typeid(*shader) == typeid(BackgroundShader) ||
                        typeid(*shader) == typeid(Normals2RGBShader) ||
                        typeid(*shader) == typeid(DepthMapShader)) {
                        scene  = *(interpretScene(lines, false));
                    } else if (typeid(*shader) == typeid(BlinnPhongShader) ||
                               typeid(*shader) == typeid(CelShader) ||
                               typeid(*shader) == typeid(LambertianShader)) {
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
         * Interpret object (like shaders, shapes, etc.) from a custom format.
         *
         * @param format Custom format object
         * @param lines File lines
         *
         * @return Content of object
         */
        static std::vector<std::string>* getContent(std::vector<std::string> format,
                std::list<std::string>& lines) {
            // Init
            std::vector<std::string>* v = new std::vector<std::string>();
            std::list<std::string>::iterator itr = lines.begin();
            std::list<std::string>::iterator begin = lines.begin();
            // Read contents
            for (std::string str : format) {
                // Check format
                if ((*itr).find(str) == 0) {
                    // Get content
                    std::string aux = *(itr++);
                    v->push_back(aux.replace(0, str.length(), ""));
                } else {
                    throw "Invalid file format.";
                }
            }
            // Remove interpreted lines
            lines.erase(begin, itr);
            return v;
        }

        /*!
         * Interpret output settings from a scene description file.
         *
         * @param lines File lines
         *
         * @return Output Settings
         */
        static OutputSettings* interpretOS(std::list<std::string>& lines) {
            // Output settings format
            std::string vformat[] = {"NAME:", "TYPE:", "CODIFICATION:",
                                     "WIDTH:", "HEIGHT:"};
            std::vector<std::string> format(vformat, end(vformat));
            // Create the output settings and return it
            std::vector<std::string>& v = *(getContent(format, lines));
            for (std::string& str : v) {
                str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
            }
            return (new OutputSettings(v[0], OutputSettings::getImageFileFormat(v[1]),
                OutputSettings::getCodification(v[2]), std::stoi(v[3]), std::stoi(v[4])));
        }

        /*!
         * Interpret ray tracing settings from a scene description file.
         * Get samples and nrays by reference.
         *
         * @param lines File lines
         */
        static void interpretRTSettings(std::list<std::string>& lines,
                int& samples, int& nrays) {
            // Camara format
            std::string vformat[] = {"SAMPLES:", "RAYS:"};
            std::vector<std::string> format(vformat, end(vformat));
            // Get contents
            std::vector<std::string>& v = *(getContent(format, lines));
            samples = atoi(v[0].c_str());
            nrays = atoi(v[1].c_str());
        }

        /*!
         * Interpret camera from a scene description file.
         *
         * @param lines File lines
         *
         * @return Readed camera
         */
        static Camera* interpretCamera(std::list<std::string>& lines) {
            // Look for other scene components
            if (!lines.empty() && (*(lines.begin())).find("CAMERA:") == 0) {
                lines.pop_front();
                if (!lines.empty() && (*(lines.begin())).find("PERSPECTIVE") == 0) {
                    lines.pop_front();
                    // Camera format
                    std::string vformat[] = {"LOOK_FROM:", "LOOK_AT:", "VUP:",
                                             "VFOV:", "ASPECT_RATIO:", "APERTURE:",
                                             "FOCAL_DISTANCE:"};
                    std::vector<std::string> format(vformat, end(vformat));
                    // Create the camera and return it
                    std::vector<std::string>& v = *(getContent(format, lines));
                    return (new PerspectiveCamera(getVec3(v[0]), getVec3(v[1]),
                        getVec3(v[2]), atof(v[3].c_str()), atof(v[4].c_str()),
                        atof(v[5].c_str()), atof(v[6].c_str())));
                } else if (!lines.empty() && (*(lines.begin())).find("PARALLEL") == 0) {
                    lines.pop_front();
                    // Camera format
                    std::string vformat[] = {"LOOK_FROM:", "LOOK_AT:", "VUP:",
                                             "TOP:", "LEFT:", "RIGHT:", "BOTTOM:"};
                    std::vector<std::string> format(vformat, end(vformat));
                    // Create the camera and return it
                    std::vector<std::string>& v = *(getContent(format, lines));
                    return (new ParallelCamera(getVec3(v[0]), getVec3(v[1]),
                        getVec3(v[2]), atof(v[3].c_str()), atof(v[4].c_str()),
                        atof(v[5].c_str()), atof(v[6].c_str())));
                } else {
                    // ERROR
                    throw "Invalid file format! Needs the camera description.";
                }
            } else {
                // ERROR
                throw "Invalid file format! Needs the camera description.";
            }
        }

        /*!
         * Interpret shader from a scene description file.
         *
         * @param lines File lines
         *
         * @return Readed shader
         */
        static Shader* interpretShader(std::list<std::string>& lines) {
            // Look for other scene components
            if (!lines.empty() && (*(lines.begin())).find("SHADER:") == 0) {
                // Remove interpreted lines
                lines.pop_front();
                std::string aux = *(lines.begin());
                lines.pop_front();
                if (aux.find("BACKGROUND") == 0) {
                    return (new BackgroundShader());
                } else
                    if (aux.find("NORMALS2RGB") == 0) {
                        return (new Normals2RGBShader());
                } else
                    if (aux.find("DEPTHMAP") == 0) {
                        return getDMShader(lines);
                } else
                    if (aux.find("BLINNPHONG") == 0) {
                        return getBPShader(lines);
                } else
                    if (aux.find("TOON") == 0) {
                        return getCelShader(lines);
                } else
                    if (aux.find("LAMBERTIAN") == 0) {
                        return (new LambertianShader());
                } else {
                    throw "Invalid shader!";
                }
            } else {
                // ERROR
                throw "Invalid file format! Needs the shader description.";
            }
        }

        /*!
         * Interpret Depth Map Shader from a scene description file.
         *
         * @param lines File lines
         *
         * @return Depth Map Shader.
         */
        static DepthMapShader* getDMShader(std::list<std::string>& lines) {
            // Depth map shader format
            std::string vformat[] = {"DEPTH:", "FOREGROUND:", "BACKGROUND:"};
            std::vector<std::string> format(vformat, end(vformat));
            // Create the shader and return it
            std::vector<std::string>& v = *(getContent(format, lines));
            return (new DepthMapShader(atof(v[0].c_str()), getVec3(v[1]),
                getVec3(v[2])));
        }

        /*!
         * Interpret Blinn-Phong Shader from a scene description file.
         *
         * @param lines File lines
         *
         * @return Blinn-Phong Shader.
         */
        static BlinnPhongShader* getBPShader(std::list<std::string>& lines) {
            // Blinn-Phong shader format
            std::string vformat[] = {"AMBIENT_LIGHT:"};
            std::vector<std::string> format(vformat, end(vformat));
            // Create the shader and return it
            std::vector<std::string>& v = *(getContent(format, lines));
            return (new BlinnPhongShader(getVec3(v[0])));
        }

        /*!
         * Interpret Cel Shader from a scene description file.
         *
         * @param lines File lines
         *
         * @return Cel Shader.
         */
        static CelShader* getCelShader(std::list<std::string>& lines) {
            // Blinn-Phong shader format
            std::string vformat[] = {"BORDER_COLOR:"};
            std::vector<std::string> format(vformat, end(vformat));
            // Create the shader and return it
            std::vector<std::string>& v = *(getContent(format, lines));
            return (new CelShader(getVec3(v[0])));
        }

        // Scene reader
        #include "scene_reader.inl"
};

#endif /* _SCENE_READER_H_ */

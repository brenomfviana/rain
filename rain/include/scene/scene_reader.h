#ifndef _SCENE_READER_H_
#define _SCENE_READER_H_

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include "vec3.h"
#include "scene.h"
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
        static Scene read(const std::string path) {
            // Open scene file
            std::ifstream file(path.c_str());
            // Check if the file exists
            if (!file) {
                // ERROR
                std::cout << "Error: The file is not exists." << std::endl;
            } else
                // Check if the file is open
                if (!file.is_open()) {
                // ERROR
                std::cout << "Error: The file could not be opened." << std::endl;
            } else {
                std::list<std::string> lines;
                // Read all lines of file and removes useless chars
                std::string line;
                while (getline(file, line)) {
                    // Remove comments
                    if (line.find("#") < line.length()) {
                        line = line.replace(line.find("#"), line.length() - 1, "");
                    }
                    // Remove indentation
                    if (line.find("    ") == 0) {
                        line = line.replace(line.find("    "), 4, "");
                    }
                    // Adds in list
                    lines.push_back(line);
                }
                // Close file
                file.close();
                // Interprets file and return a scene
                return interpretFile(lines);
            }
            // Empty scene
            return Scene();
        }

    private:
        /*!
         * Split a string and get an array with three cells.
         *
         * @param str String to be splited
         *
         * @return An array with RGB values
         */
        static std::string* splitRGB(std::string str) {
            //
            std::string* vstr = new std::string[3];
            //
            for (int i = 0; i < 3; i++) {
                int pos = str.find(" ");
                std::string t = str.substr(0, pos);
                vstr[i] = t;
                str.erase(0, pos + 1);
            }
            return vstr;
        }

        /**
         * Interpret the scene file.
         *
         * @param lines File lines
         *
         * @return Interpreted scene
         */
        static Scene interpretFile(std::list<std::string> lines) {
            // Scene header format
            std::string header[] = {"NAME: ", "TYPE: ", "CODIFICATION: ",
                               "WIDTH: ", "HEIGHT: ", "BACKGROUND:"};
            enum SceneHeader : int {NAME = 0, TYPE = 1, CODIFICATION = 2, WIDTH = 3,
                                    HEIGHT = 4, BACKGROUND = 5};
            // Scene attributes
            std::string name;
            std::string type;
            std::string codification;
            unsigned int width;
            unsigned int height;
            Background* background = new Background();
            // Interpret scene file
            std::list<std::string>::iterator itr = lines.begin();
            // Get image name
            if ((*itr).find(header[NAME]) == 0) {
                std::string n = header[NAME];
                std::string as = *(itr);
                name = as.replace(0, n.length(), "");
                itr++;
                // Get image type
                if ((*itr).find(header[TYPE]) == 0) {
                    std::string n = header[TYPE];
                    std::string as = *(itr);
                    type = as.replace(0, n.length(), "");
                    itr++;
                    // Get image codification
                    if ((*itr).find(header[CODIFICATION]) == 0) {
                        std::string n = header[CODIFICATION];
                        std::string as = *(itr);
                        codification = as.replace(0, n.length(), "");
                        itr++;
                        // Get image width
                        if ((*itr).find(header[WIDTH]) == 0) {
                            std::string n = header[WIDTH];
                            std::string as = *(itr);
                            width = std::stoi(as.replace(0, n.length(), ""));
                            itr++;
                            // Get image height
                            if ((*itr).find(header[HEIGHT]) == 0) {
                                std::string n = header[HEIGHT];
                                std::string as = *(itr);
                                height = std::stoi(as.replace(0, n.length(), ""));
                                itr++;
                                // Get scene background
                                if ((*itr).find(header[BACKGROUND]) == 0) {
                                    // Upper left corner
                                    std::string n = "UPPER_LEFT: ";
                                    ++itr;
                                    std::string as = *(itr);
                                    as.replace(0, n.length(), "");
                                    std::string* t0 = splitRGB(as);
                                    background->upperLeft = RGB(
                                        (atof(t0[0].c_str()) / 255),
                                        (atof(t0[1].c_str()) / 255),
                                        (atof(t0[2].c_str())) / 255);
                                    // Lower left corner
                                    n = "LOWER_LEFT: ";
                                    ++itr;
                                    as = *(itr);
                                    as.replace(0, n.length(), "");
                                    std::string* t1 = splitRGB(as);
                                    background->lowerLeft = RGB(
                                        (atof(t1[0].c_str()) / 255),
                                        (atof(t1[1].c_str()) / 255),
                                        (atof(t1[2].c_str())) / 255);
                                    // Upper right corner
                                    n = "UPPER_RIGHT: ";
                                    ++itr;
                                    as = *(itr);
                                    as.replace(0, n.length(), "");
                                    std::string* t2 = splitRGB(as);
                                    background->upperRight = RGB(
                                        (atof(t2[0].c_str()) / 255),
                                        (atof(t2[1].c_str()) / 255),
                                        (atof(t2[2].c_str())) / 255);
                                    // Lower right corner
                                    n = "LOWER_RIGHT: ";
                                    ++itr;
                                    as = *(itr);
                                    as.replace(0, n.length(), "");
                                    std::string* t3 = splitRGB(as);
                                    background->lowerRight = RGB(
                                        (atof(t3[0].c_str()) / 255),
                                        (atof(t3[1].c_str()) / 255),
                                        (atof(t3[2].c_str())) / 255);
                                    // Return scene
                                    return Scene(name, type, codification, width, height, *background);
                                } else {
                                    // ERROR
                                    std::cout << "Error: Invalid file!" << std::endl;
                                }
                            } else {
                                // ERROR
                                std::cout << "Error: Invalid file!" << std::endl;
                            }
                        } else {
                            // ERROR
                            std::cout << "Error: Invalid file!" << std::endl;
                        }
                    } else {
                        // ERROR
                        std::cout << "Error: Invalid file!" << std::endl;
                    }
                } else {
                    // ERROR
                    std::cout << "Error: Invalid file!" << std::endl;
                }
            } else {
                // ERROR
                std::cout << "Error: Invalid file!" << std::endl;
            }
            // Empty scene
            return Scene();
        }
};

#endif

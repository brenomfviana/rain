#include <string>
#include "utils/vec3.h"
#include "scene/scene_reader.h"

Scene SceneReader::read(const std::string path) {
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

RGB SceneReader::splitRGB(std::string str) {
    // Auxiliary vector
    std::string* vstr = new std::string[3];
    // Conversion
    for (int i = 0; i < 3; i++) {
        int pos = str.find(" ");
        std::string t = str.substr(0, pos);
        vstr[i] = t;
        str.erase(0, pos + 1);
    }
    // Generate RGB
    RGB rgb = RGB((atof(vstr[0].c_str()) / 255),
                  (atof(vstr[1].c_str()) / 255),
                  (atof(vstr[2].c_str()) / 255));
    return rgb;
}

Scene SceneReader::interpretFile(std::list<std::string> lines) {
    // Scene header format
    std::string header[] = {"NAME: ", "TYPE: ", "CODIFICATION: ",
                       "WIDTH: ", "HEIGHT: ", "BACKGROUND:"};
    enum SceneHeader : int {NAME = 0, TYPE = 1, CODIFICATION = 2, WIDTH = 3,
                            HEIGHT = 4, BACKGROUND = 5};
    // Scene attributes
    std::string name;
    ImageFileFormats type;
    Codifications codification;
    unsigned int width;
    unsigned int height;
    Background* background = new Background();
    // Interpret scene file
    std::list<std::string>::iterator itr = lines.begin();
    // Get image name
    if ((*itr).find(header[NAME]) == 0) {
        std::string n = header[NAME];
        std::string aux = *(itr);
        name = aux.replace(0, n.length(), "");
        // Get image type
        if ((*++itr).find(header[TYPE]) == 0) {
            std::string n = header[TYPE];
            std::string aux = *(itr);
            type = getImageFileFormat(aux.replace(0, n.length(), ""));
            // Get image codification
            if ((*++itr).find(header[CODIFICATION]) == 0) {
                std::string n = header[CODIFICATION];
                std::string aux = *(itr);
                codification = getCodification(aux.replace(0, n.length(), ""));
                // Get image width
                if ((*++itr).find(header[WIDTH]) == 0) {
                    std::string n = header[WIDTH];
                    std::string aux = *(itr);
                    width = std::stoi(aux.replace(0, n.length(), ""));
                    // Get image height
                    if ((*++itr).find(header[HEIGHT]) == 0) {
                        std::string n = header[HEIGHT];
                        std::string aux = *(itr);
                        height = std::stoi(aux.replace(0, n.length(), ""));
                        // Get scene background
                        if ((*++itr).find(header[BACKGROUND]) == 0) {
                            // Upper left corner
                            std::string n = "UPPER_LEFT: ";
                            std::string aux = *(++itr);
                            aux.replace(0, n.length(), "");
                            background->upperLeft = splitRGB(aux);
                            // Lower left corner
                            n = "LOWER_LEFT: ";
                            aux = *(++itr);
                            aux.replace(0, n.length(), "");
                            background->lowerLeft = splitRGB(aux);
                            // Upper right corner
                            n = "UPPER_RIGHT: ";
                            aux = *(++itr);
                            aux.replace(0, n.length(), "");
                            background->upperRight = splitRGB(aux);
                            // Lower right corner
                            n = "LOWER_RIGHT: ";
                            aux = *(++itr);
                            aux.replace(0, n.length(), "");
                            background->lowerRight = splitRGB(aux);
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

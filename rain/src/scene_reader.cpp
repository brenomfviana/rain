#include "utils/split.h"
#include "render/io/scene_reader.h"

void SceneReader::read(const std::string path, Scene& scene, Camera& cam, OutputSettings& os) {
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

OutputSettings* SceneReader::interpretOutputSettings(std::list<std::string>& lines) {
    // Header size
    int hsize = 5;
    // Scene header format
    std::string header[] = {"NAME: ", "TYPE: ", "CODIFICATION: ",
                       "WIDTH: ", "HEIGHT: "};
    // Interpret file
    std::list<std::string>::iterator itr = lines.begin(), ib = lines.begin();
    for (int i = 0; i < hsize; i++) {
        // Check header
        if ((*itr).find(header[i]) == 0) {
            std::string n = header[i];
            std::string aux = *(itr++);
            header[i] = aux.replace(0, n.length(), "");
        } else {
            // ERROR
            throw "Invalid file!";
        }
    }
    // Remove interpreted lines
    lines.erase(ib, itr);
    // Create image
    OutputSettings* os = new OutputSettings(std::stoi(header[3]), std::stoi(header[4]), header[0],
        OutputSettings::getImageFileFormat(header[1]), OutputSettings::getCodification(header[2]));
    return os;
}

Camera* SceneReader::interpretCamera(std::list<std::string>& lines) {
    // Header size
    int hsize = 4;
    // Camara header format
    std::string header[] = {"LLC: ", "H: ", "V: ", "O: "};
    // Interpret file
    std::list<std::string>::iterator itr = lines.begin(), ib = lines.begin();
    for (int i = 0; i < hsize; i++) {
        // Check header
        if ((*itr).find(header[i]) == 0) {
            std::string n = header[i];
            std::string aux = *(itr++);
            header[i] = aux.replace(0, n.length(), "");
        } else {
            // ERROR
            throw "Invalid file!";
        }
    }
    // Remove interpreted lines
    lines.erase(ib, itr);
    Camera* cam = new Camera(getVec3(header[0]), getVec3(header[1]),
        getVec3(header[2]), getVec3(header[3]));
    return cam;
}

Vec3 SceneReader::getVec3(std::string str) {
    // Auxiliary vector
    std::vector<std::string> v = split(str, ' ');
    // Generate Vec3
    RGB rgb = Vec3(atof(v[0].c_str()),
                  atof(v[1].c_str()),
                  atof(v[2].c_str()));
    return rgb;
}

Scene* SceneReader::interpretScene(std::list<std::string>& lines) {
    // Scene attributes
    Background* background = new Background();
    // Interpret scene file
    std::list<std::string>::iterator itr = lines.begin(), ib = lines.begin();
    if ((*itr).find("BACKGROUND:") == 0) {
        // Upper left corner
        std::string n = "UPPER_LEFT: ";
        std::string aux = *(++itr);
        aux.replace(0, n.length(), "");
        background->upperLeft = getRGB(aux);
        // Lower left corner
        n = "LOWER_LEFT: ";
        aux = *(++itr);
        aux.replace(0, n.length(), "");
        background->lowerLeft = getRGB(aux);
        // Upper right corner
        n = "UPPER_RIGHT: ";
        aux = *(++itr);
        aux.replace(0, n.length(), "");
        background->upperRight = getRGB(aux);
        // Lower right corner
        n = "LOWER_RIGHT: ";
        aux = *(++itr);
        aux.replace(0, n.length(), "");
        background->lowerRight = getRGB(aux);
    } else {
        // ERROR
        throw "Invalid file!";
    }
    Scene* scene = new Scene(*background);
    // Remove interpreted lines
    itr++;
    lines.erase(ib, itr);
    // Look for other scene components
    if (!lines.empty() && (*(itr)).find("COMPONENTS:") == 0) {
        lines.erase(itr);
        for (itr = lines.begin(); !lines.empty(); ) {
            //
            if ((*(itr)).find("SPHERE:") == 0) {
                lines.erase(itr);
                Sphere* s = getSphere(lines);
                scene->addShape(s);
                itr = lines.begin();
            }
        }
    }
    return scene;
}

RGB SceneReader::getRGB(std::string str) {
    // Auxiliary vector
    std::vector<std::string> v = split(str, ' ');
    // Generate RGB
    RGB rgb = RGB((atof(v[0].c_str()) / 255.f),
                  (atof(v[1].c_str()) / 255.f),
                  (atof(v[2].c_str()) / 255.f));
    return rgb;
}

Sphere* SceneReader::getSphere(std::list<std::string>& lines) {
    // Header size
    int hsize = 2;
    // Camara header format
    std::string header[] = {"O: ", "RADIUS: "};
    // Interpret file
    std::list<std::string>::iterator itr = lines.begin(), ib = lines.begin();
    for (int i = 0; i < hsize; i++) {
        // Check header
        if ((*itr).find(header[i]) == 0) {
            std::string n = header[i];
            std::string aux = *(itr++);
            header[i] = aux.replace(0, n.length(), "");
        } else {
            // ERROR
            throw "Invalid file!";
        }
    }
    // Remove interpreted lines
    lines.erase(ib, itr);
    Sphere* s = new Sphere(getVec3(header[0]), atof(header[1].c_str()));
    return s;
}

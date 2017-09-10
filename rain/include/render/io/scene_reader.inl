#include "scene_reader.h"

/*!
 * Interpret a 3D vector.
 *
 * @param str String that corresponds to a vector
 *
 * @return 3D vector
 */
static Vec3 getVec3(std::string str) {
    // Auxiliary vector
    std::vector<std::string> v = split(str, ' ');
    // Generate Vec3
    Vec3 vec = Vec3(atof(v[0].c_str()),
                  atof(v[1].c_str()),
                  atof(v[2].c_str()));
    return vec;
}

/*!
 * Interpret a RGB color.
 *
 * @param str String that corresponds to a RGB vector
 *
 * @return RGB color
 */
static RGB getRGB(std::string str) {
    return (getVec3(str) / 255.f);
}

/*!
 * Interpret a scene file.
 *
 * @param lines File lines
 * @param md If needs material description
 *
 * @return Interpreted scene
 */
static Scene* interpretScene(std::list<std::string>& lines, bool md) {
    // Check if scene description is empty
    if (lines.empty()) {
        return new Scene();
    }
    // Interpret scene attributes
    std::list<std::string>::iterator itr = lines.begin();
    // Scene background
    Background* background;
    if ((*itr).find("BACKGROUND:") == 0) {
        lines.erase(itr);
        background = getBackground(lines);
    }
    Scene* scene = new Scene(*background);
    // Check if scene description is empty
    if (lines.empty()) {
        return scene;
    }
    // Components
    itr = lines.begin();
    // Look for other scene components
    if (!lines.empty() && (*(itr)).find("COMPONENTS:") == 0) {
        // Erase
        lines.erase(itr);
        // Find components
        for (itr = lines.begin(); !lines.empty(); ) {
            // Check all components
            if ((*(itr)).find("LIGHT:") == 0) {
                // Erase
                lines.erase(itr);
                // Add light
                Light* l = getLight(lines);
                scene->addLight(l);
                // Next component
                itr = lines.begin();
            } else if ((*(itr)).find("SPHERE:") == 0) {
                // Erase
                lines.erase(itr);
                // Add sphere
                Sphere* s = getSphere(lines, md);
                scene->addShape(s);
                // Next component
                itr = lines.begin();
            }
        }
    }
    return scene;
}

/*!
 * Get background description.
 *
 * @param lines File lines
 *
 * @return Background
 */
static Background* getBackground(std::list<std::string>& lines) {
    // Background formats
    int f1size = 4;
    std::string f1[] = {"UPPER_LEFT: ", "LOWER_LEFT: ",
                        "UPPER_RIGHT: ", "LOWER_RIGHT: "};
    int f23size = 2;
    std::string f2[] = {"TOP: ", "BOTTOM: "};
    std::string f3[] = {"LEFT: ", "RIGHT: "};
    std::string f4[] = {"COLOR: "};
    // Interpret scene file
    std::list<std::string>::iterator itr = lines.begin();
    std::list<std::string>::iterator begin = lines.begin();
    Background* background;
    // Check description type
    // Corners
    if ((*itr).find(f1[0]) == 0) {
        for (int i = 0; i < f1size; i++) {
            // Check format
            if ((*itr).find(f1[i]) == 0) {
                std::string aux = *(itr++);
                f1[i] = aux.replace(0, f1[i].length(), "");
            } else {
                // ERROR
                throw "Invalid file!";
            }
        }
        background = new Background(getRGB(f1[0]), getRGB(f1[1]),
                                    getRGB(f1[2]), getRGB(f1[3]));
    } else
        // Top-Bottom
        if ((*itr).find(f2[0]) == 0) {
        for (int i = 0; i < f23size; i++) {
            // Check format
            if ((*itr).find(f2[i]) == 0) {
                std::string aux = *(itr++);
                f2[i] = aux.replace(0, f2[i].length(), "");
            } else {
                // ERROR
                throw "Invalid file!";
            }
        }
        background = new Background(getRGB(f2[0]), getRGB(f2[1]), true);
    } else
        // Left-Right
        if ((*itr).find(f3[0]) == 0) {
        for (int i = 0; i < f23size; i++) {
            // Check format
            if ((*itr).find(f3[i]) == 0) {
                std::string aux = *(itr++);
                f3[i] = aux.replace(0, f3[i].length(), "");
            } else {
                // ERROR
                throw "Invalid file!";
            }
        }
        background = new Background(getRGB(f3[0]), getRGB(f3[1]), false);
    } else
        // One color
        if ((*itr).find(f4[0]) == 0) {
        f4[0].replace(0, f4[0].length(), "");
        background = new Background(getRGB(f4[0]));
    }
    // Remove interpreted lines
    lines.erase(begin, itr);
    return background;
}

/*!
 * Get light description.
 *
 * @param lines File lines
 *
 * @return Light
 */
static Light* getLight(std::list<std::string>& lines) {
    // Format size
    int fsize = 2;
    // Light format
    std::string format[] = {"DIRECTION: ", "INTENSITY: "};
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
    Light* l = new Light(getVec3(format[0]), getRGB(format[1].c_str()));
    return l;
}


/*!
 * Get sphere description.
 *
 * @param lines File lines
 *
 * @return Sphere
 */
static Sphere* getSphere(std::list<std::string>& lines, bool md) {
    // Format size
    int fsize = 2;
    // Sphere format
    std::string format[] = {"ORIGIN: ", "RADIUS: "};
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
    Sphere* s;
    if (md) {
        s = new Sphere(getVec3(format[0]), atof(format[1].c_str()),
            getMaterial(lines));
    } else {
        s = new Sphere(getVec3(format[0]), atof(format[1].c_str()));
    }
    return s;
}

#include "material_reader.inl"

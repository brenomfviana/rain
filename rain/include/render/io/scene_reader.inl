#include "scene_reader.h"

/*!
 * Interpret a 3D vector from a string.
 *
 * @param str String that corresponds to a vector
 *
 * @return 3D vector
 */
static Vec3 getVec3(std::string str) {
    // Auxiliary vector
    std::vector<std::string> v = split(str, ' ');
    for (std::string& str : v) {
        str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
    }
    // Generate Vec3
    Vec3 vec = Vec3(atof(v[0].c_str()), atof(v[1].c_str()), atof(v[2].c_str()));
    return vec;
}

/*!
 * Interpret a scene from a scene description file.
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
            if ((*(itr)).find("DIRECTIONAL_LIGHT:") == 0) {
                // Erase
                lines.erase(itr);
                // Add light
                Light* l = getDirectionalLight(lines);
                scene->addLight(l);
                // Next component
                itr = lines.begin();
            } else if ((*(itr)).find("POINT_LIGHT:") == 0) {
                // Erase
                lines.erase(itr);
                // Add light
                Light* l = getPointLight(lines);
                scene->addLight(l);
                // Next component
                itr = lines.begin();
            } else if ((*(itr)).find("SPOTLIGHT:") == 0) {
                // Erase
                lines.erase(itr);
                // Add light
                Light* l = getSpotlight(lines);
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
    std::string f1[] = {"UPPER_LEFT:", "LOWER_LEFT:", "UPPER_RIGHT:",
                        "LOWER_RIGHT:"};
    std::string f2[] = {"TOP:", "BOTTOM:"};
    std::string f3[] = {"LEFT:", "RIGHT:"};
    std::string f4[] = {"COLOR:"};
    // Interpret background
    Background* background;
    // Check description type
    std::string aux = *(lines.begin());
    // Corners
    if (aux.find(f1[0]) == 0) {
        std::vector<std::string> format(f1, end(f1));
        // Create the background and return it
        std::vector<std::string>& v = *(getContent(format, lines));
        background = new Background(getVec3(v[0]), getVec3(v[1]), getVec3(v[2]),
            getVec3(v[3]));
    } else
        // Top-Bottom
        if (aux.find(f2[0]) == 0) {
            std::vector<std::string> format(f2, end(f2));
            // Create the background and return it
            std::vector<std::string>& v = *(getContent(format, lines));
            background = new Background(getVec3(v[0]), getVec3(v[1]), true);
    } else
        // Left-Right
        if (aux.find(f3[0]) == 0) {
            std::vector<std::string> format(f3, end(f3));
            // Create the background and return it
            std::vector<std::string>& v = *(getContent(format, lines));
            background = new Background(getVec3(v[0]), getVec3(v[1]), false);
    } else
        // One color
        if (aux.find(f4[0]) == 0) {
            std::vector<std::string> format(f4, end(f4));
            // Create the background and return it
            std::vector<std::string>& v = *(getContent(format, lines));
            background = new Background(getVec3(v[0]));
    }
    return background;
}

/*!
 * Get directional light description.
 *
 * @param lines File lines
 *
 * @return Light
 */
static DirectionalLight* getDirectionalLight(std::list<std::string>& lines) {
    // Directional light format
    std::string vformat[] = {"DIRECTION:", "INTENSITY:"};
    std::vector<std::string> format(vformat, end(vformat));
    // Create the directional light and return it
    std::vector<std::string>& v = *(getContent(format, lines));
    return (new DirectionalLight(getVec3(v[0]), getVec3(v[1].c_str())));
}

/*!
 * Get Point light description.
 *
 * @param lines File lines
 *
 * @return Point light
 */
static PointLight* getPointLight(std::list<std::string>& lines) {
    // Spot light format
    std::string vformat[] = {"ORIGIN:", "INTENSITY:"};
    std::vector<std::string> format(vformat, end(vformat));
    // Create the spot light and return it
    std::vector<std::string>& v = *(getContent(format, lines));
    return (new PointLight(getVec3(v[0].c_str()), getVec3(v[1].c_str())));
}

/*!
 * Get spot light description.
 *
 * @param lines File lines
 *
 * @return Spotlight
 */
static Spotlight* getSpotlight(std::list<std::string>& lines) {
    // Spot light format
    std::string vformat[] = {"ORIGIN:", "DIRECTION:", "INTENSITY:", "ANGLE:"};
    std::vector<std::string> format(vformat, end(vformat));
    // Create the spot light and return it
    std::vector<std::string>& v = *(getContent(format, lines));
    return (new Spotlight(getVec3(v[0].c_str()), getVec3(v[1].c_str()),
            getVec3(v[2].c_str()), atof(v[3].c_str())));
}


/*!
 * Get sphere description.
 *
 * @param lines File lines
 *
 * @return Sphere
 */
static Sphere* getSphere(std::list<std::string>& lines, bool md) {
    // Sphere format
    std::string vformat[] = {"ORIGIN:", "RADIUS:"};
    std::vector<std::string> format(vformat, end(vformat));
    // Create the sphere and return it
    std::vector<std::string>& v = *(getContent(format, lines));
    Sphere* s;
    if (md) {
        s = new Sphere(getVec3(v[0]), atof(v[1].c_str()), getMaterial(lines));
    } else {
        s = new Sphere(getVec3(v[0]), atof(v[1].c_str()));
    }
    return s;
}

#include "material_reader.inl"

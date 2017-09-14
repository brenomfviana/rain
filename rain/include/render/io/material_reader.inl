#include "scene_reader.h"

/*!
 * Get material description.
 *
 * @param lines File lines
 *
 * @return Material
 */
static Material* getMaterial(std::list<std::string>& lines) {
    // Interpret file
    std::list<std::string>::iterator itr = lines.begin();
    if ((*itr).find("BLINN_PHONG_MATERIAL:") == 0) {
        lines.erase(itr);
        return getBlinnPhongMaterial(lines);
    } else if ((*itr).find("LAMBERTIAN:") == 0) {
        lines.erase(itr);
        return getLambertianMaterial(lines);
    } else if ((*itr).find("METAL:") == 0) {
        lines.erase(itr);
        return getMetalMaterial(lines);
    } else {
        throw "Invalid shader!";
    }
}

/*!
 * .
 */
static BlinnPhongMaterial* getBlinnPhongMaterial(std::list<std::string>& lines) {
    // Format size
    int fsize = 4;
    // Material format
    std::string format[] = {"KA: ", "KD: ", "KS: ", "P: "};
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
    BlinnPhongMaterial* bpm = new BlinnPhongMaterial(getVec3(format[0]),
        getVec3(format[1]), getVec3(format[2]), atof(format[3].c_str()));
    return bpm;
}

/*!
 * .
 */
static LambertianMaterial* getLambertianMaterial(std::list<std::string>& lines) {
    // Format size
    int fsize = 1;
    // Material format
    std::string format[] = {"ALBEDO: "};
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
    LambertianMaterial* l = new LambertianMaterial(getVec3(format[0]));
    return l;
}

/*!
 * .
 */
static MetalMaterial* getMetalMaterial(std::list<std::string>& lines) {
    // Format size
    int fsize = 2;
    // Material format
    std::string format[] = {"ALBEDO: ", "FUZZ: "};
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
    MetalMaterial* l = new MetalMaterial(getVec3(format[0]),
        atof(format[1].c_str()));
    return l;
}

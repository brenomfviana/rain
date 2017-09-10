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
    /*} else if (aux.find("METAL:") == 0) {
        return getMetalMaterial(lines);*/
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
    // Sphere format
    std::string format[] = {"KD: ", "KS: ", "P: ", "KA: "};
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
    BlinnPhongMaterial* bpm = new BlinnPhongMaterial(getRGB(format[0]),
        getRGB(format[1]), atof(format[2].c_str()), getRGB(format[3]));
    return bpm;
}

/*!
 * .
 */
static LambertianMaterial* getLambertianMaterial(std::list<std::string>& lines) {
    // Format size
    int fsize = 1;
    // Sphere format
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
    LambertianMaterial* l = new LambertianMaterial(getRGB(format[0]));
    return l;
}

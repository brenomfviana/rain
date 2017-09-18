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
    std::string aux = *(lines.begin());
    lines.pop_front();
    if (aux.find("BLINN_PHONG_MATERIAL:") == 0) {
        return getBPMaterial(lines);
    } else
        if (aux.find("LAMBERTIAN:") == 0) {
            return getLambertianMaterial(lines);
    } else
        if (aux.find("METAL:") == 0) {
            return getMetalMaterial(lines);
    } else
        if (aux.find("DIELECTRIC:") == 0) {
            return getDielectricMaterial(lines);
    } else {
        throw "Invalid shader!";
    }
}

/*!
 * Get Blinn-Phong material.
 *
 * @param lines File lines
 *
 * @return Blinn-Phong material
 */
static BlinnPhongMaterial* getBPMaterial(std::list<std::string>& lines) {
    // Material format
    std::string vformat[] = {"KA:", "KD:", "KS:", "P:"};
    std::vector<std::string> format(vformat, end(vformat));
    // Create the Blinn-Phong material and return it
    std::vector<std::string>& v = *(getContent(format, lines));
    return (new BlinnPhongMaterial(getVec3(v[0]), getVec3(v[1]), getVec3(v[2]),
        atof(v[3].c_str())));
}

/*!
 * Get Lambertian material.
 *
 * @param lines File lines
 *
 * @return Lambertian material
 */
static LambertianMaterial* getLambertianMaterial(std::list<std::string>& lines) {
    // Material format
    std::string vformat[] = {"ALBEDO:"};
    std::vector<std::string> format(vformat, end(vformat));
    // Create the Lambertian material and return it
    std::vector<std::string>& v = *(getContent(format, lines));
    return (new LambertianMaterial(getVec3(v[0])));
}

/*!
 * Get Metal material.
 *
 * @param lines File lines
 *
 * @return Metal material
 */
static MetalMaterial* getMetalMaterial(std::list<std::string>& lines) {
    // Material format
    std::string vformat[] = {"ALBEDO:", "FUZZ:"};
    std::vector<std::string> format(vformat, end(vformat));
    // Create the Metal material and return it
    std::vector<std::string>& v = *(getContent(format, lines));
    return (new MetalMaterial(getVec3(v[0]), atof(v[1].c_str())));
}

/*!
 * Get Dielectric material.
 *
 * @param lines File lines
 *
 * @return Dielectric material
 */
static DielectricMaterial* getDielectricMaterial(std::list<std::string>& lines) {
    // Material format
    std::string vformat[] = {"RI:"};
    std::vector<std::string> format(vformat, end(vformat));
    // Create the Metal material and return it
    std::vector<std::string>& v = *(getContent(format, lines));
    return (new DielectricMaterial(atof(v[0].c_str())));
}

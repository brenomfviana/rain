#ifndef _IMAGE_FILE_FORMATS_H_
#define _IMAGE_FILE_FORMATS_H_

#include <string>

// Supported file formats
enum ImageFileFormats {PPM = 0, BMP = 1, JPG = 2, PNG = 3,
                       TIFF = 4, GIF = 5};

// Codifications
enum Codifications {ASCII = 0, BINARY = 1};

/*!
 * TO COMMENT.
 */
inline ImageFileFormats getImageFileFormat(std::string str) {
    // Check file format
    if (str.find("PPM") == 0) {
        return PPM;
    } else if (str.find("BMP") == 0) {
        return BMP;
    } else if (str.find("JPG") == 0) {
        return JPG;
    } else if (str.find("PNG") == 0) {
        return PNG;
    } else if (str.find("TIFF") == 0) {
        return TIFF;
    } else if (str.find("GIF") == 0) {
        return GIF;
    } else {
        // ERROR
        throw "Invalid image file format!";
    }
}

/*!
 * TO COMMENT.
 */
inline Codifications getCodification(std::string str) {
    // Check file format
    if (str.find("ascii") == 0) {
        return ASCII;
    } else if (str.find("binary") == 0) {
        return BINARY;
    } else {
        // ERROR
        throw "Invalid codification!";
    }
}

#endif

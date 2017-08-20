#ifndef _OUTPUT_SETTINGS_H_
#define _OUTPUT_SETTINGS_H_

#include <string>

/*!
 * This class represents the output settings.
 */
class OutputSettings {

    public:
        // Supported file formats
        enum ImageFileFormats : int {PPM = 0, BMP = 1, JPG = 2, PNG = 3, TIFF = 4, GIF = 5};
        // Codifications
        enum Codifications : int {ASCII = 0, BINARY = 1};

        // Image width
        unsigned int width;
        // Image height
        unsigned int height;
        // Image name
        std::string name;
        // File format
        ImageFileFormats fileFormat;
        // Image file codification
        Codifications codification;

        /*!
         * Output settings constructor.
         *
         * @param width_ Image width
         * @param height_ Image height
         * @param name_ Image name
         * @param fileFormat_ Image file format
         * @param codification_ Image file codification
         */
        OutputSettings(int width_ = 0, int height_ = 0, std::string name_ = "unknown",
            ImageFileFormats fileFormat_ = PPM, Codifications codification_ = BINARY) :
            width(width_), height(height_), name(name_), fileFormat(fileFormat_),
            codification(codification_) { /* empty */ }

        /*!
         * Get image file format.
         *
         * @param str String that matches the image file format
         *
         * @return Image file format
         */
        inline static ImageFileFormats getImageFileFormat(std::string str) {
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
         * Get file codification.
         *
         * @param str String that matches the file codification
         *
         * @return File codification
         */
        inline static Codifications getCodification(std::string str) {
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
};

#endif

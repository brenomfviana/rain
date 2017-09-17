#ifndef _OUTPUT_SETTINGS_H_
#define _OUTPUT_SETTINGS_H_

#include <string>

/*!
 * This class is responsible for the image output settings. Output settings are
 * the image file format and file codification.
 */
class OutputSettings {

    public:
        // Supported file formats
        enum ImageFileFormats : int {PPM = 0, BMP, JPG, PNG, TIFF, GIF};
        // File codifications
        enum Codifications : int {ASCII = 0, BINARY};

        // Image name
        std::string name;
        // File format
        ImageFileFormats fileFormat;
        // Image file codification
        Codifications codification;
        // Image width
        unsigned int width;
        // Image height
        unsigned int height;

        /*!
         * Output settings constructor.
         *
         * @param name Image name
         * @param fileFormat Image file format
         * @param codification Image file codification
         * @param width Image width
         * @param height Image height
         */
        OutputSettings(std::string name = "unknown",
                ImageFileFormats fileFormat = PPM,
                Codifications codification = BINARY,
                int width = 0, int height = 0) :
            name(name), fileFormat(fileFormat), codification(codification),
            width(width), height(height) { /* empty */ }

        /*!
         * Get image file format.
         *
         * @param str String that corresponds the image file format
         *
         * @return Image file format
         */
        inline static ImageFileFormats getImageFileFormat(std::string str) {
            // Check image file format
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
         * @param str String that corresponds the file codification
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

#endif /* _OUTPUT_SETTINGS_H_ */

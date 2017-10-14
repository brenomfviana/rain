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
        enum ImageFileFormats : int {PPM = 0};
        // File codifications
        enum Codifications : int {ASCII = 0, BINARY};

        // Image name
        std::string name;
        // File format
        ImageFileFormats file_format;
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
        OutputSettings(std::string name = "unknown.ppm", ImageFileFormats file_format = PPM,
            Codifications codification = BINARY, int width = 0, int height = 0);

        /*!
         * Output settings destructor.
         */
        ~OutputSettings();

        /*!
         * Get image file format.
         *
         * @param str String that corresponds the image file format
         *
         * @return Image file format
         */
        static ImageFileFormats get_image_file_format(std::string str);

        /*!
         * Get file codification.
         *
         * @param str String that corresponds the file codification
         *
         * @return File codification
         */
        static Codifications get_codification(std::string str);
};

#endif /* _OUTPUT_SETTINGS_H_ */

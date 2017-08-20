#ifndef _IMAGE_H_
#define _IMAGE_H_

#include <string>
#include "printer/image_file_formats.h"

/*!
 * This class represents an image.
 */
class Image {

    public:
        // Image pixels
        char* pixels;
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
         * Image constructor.
         *
         * @param width_ Image width
         * @param height_ Image height
         * @param name_ Image name
         * @param fileFormat_ Image file format
         * @param codification_ Image file codification
         */
        Image(int width_ = 0, int height_ = 0, std::string name_ = "unknown",
            ImageFileFormats fileFormat_ = PPM, Codifications codification_ = BINARY) :
            width(width_), height(height_), name(name_), fileFormat(fileFormat_),
            codification(codification_) {
            // Allocate pixel vector of image
            pixels = new char[width * height * 3];
            // Initialize pixels
            for (unsigned int row = 0; row < height; row++) {
    		   	for (unsigned int col = 0; col < width; col++) {
                    pixels[(row * width * 3) + (col * 3)] = 0;
                    pixels[(row * width * 3) + (col * 3) + 1] = 0;
                    pixels[(row * width * 3) + (col * 3) + 2] = 0;
                }
            }
        }

        /*!
         * Image destructor.
         */
        ~Image() {
            delete [] pixels;
        }
};

#endif

#ifndef _IMAGE_H_
#define _IMAGE_H_

class Image {

    public:
        // Image pixels
        unsigned char* pixels;
        // Image width
        unsigned int width;
        // Image height
        unsigned int height;

        /**
         * Image constructor.
         *
         * @param width_ Image width
         * @param height_ Image height
         */
        Image(int width_ = 0, int height_ = 0) : width(width_), height(height_) {
            // Allocate pixel vector of image
            pixels = new char(3 * width * height);
        }
};

#endif

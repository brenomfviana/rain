#ifndef _IMAGE_H_
#define _IMAGE_H_

namespace utils {

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

            /*!
             * Image constructor.
             *
             * @param width_ Image width
             * @param height_ Image height
             */
            Image(unsigned int width_ = 0, unsigned int height_ = 0) :
                    width(width_), height(height_) {
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
} // namespace utils

#endif /* _IMAGE_H_ */

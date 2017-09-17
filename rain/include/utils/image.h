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
             * @param width Image width
             * @param height Image height
             */
            Image(unsigned int width = 0, unsigned int height = 0) :
                    width(width), height(height) {
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

#ifndef _PRINTER_H_
#define _PRINTER_H_

#include "image/image.h"

/*!
 * This class is responsible for printing images.
 */
class Printer {

    public:
        /*!
         * Print image.
         *
         * @param img Image to be printed
         * @param target Target folder
         */
        static void print(Image& img, std::string target);

    private:
        /*!
         * Print image in ASCII.
         *
         * @param img Image to be printed
         * @param target Target folder
         */
        static void asciiPPM(Image& img, std::string target);

        /*!
         * Print image in binary.
         *
         * @param img Image to be printed
         * @param target Target folder
         */
        static void binaryPPM(Image& img, std::string target);
};

#endif

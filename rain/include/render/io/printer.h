#ifndef _PRINTER_H_
#define _PRINTER_H_

#include <fstream>
#include "image/image.h"
#include "output_settings.h"

/*!
 * This class is responsible for printing images.
 */
class Printer {

    public:
        /*!
         * Print image.
         *
         * @param img Image to be printed
         * @param os Output settings
         * @param target Target folder
         */
        static void print(Image& img, OutputSettings& os, std::string target);

    private:
        /*!
         * Print image in ASCII.
         *
         * @param img Image to be printed
         * @param os Output settings
         * @param target Target folder
         */
        static void asciiPPM(Image& img, OutputSettings& os, std::string target);

        /*!
         * Print image in binary.
         *
         * @param img Image to be printed
         * @param os Output settings
         * @param target Target folder
         */
        static void binaryPPM(Image& img, OutputSettings& os, std::string target);
};

#endif

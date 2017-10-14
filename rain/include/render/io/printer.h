#ifndef _PRINTER_H_
#define _PRINTER_H_

#include <fstream>
#include <string>
#include "image.h"
#include "output_settings.h"

using namespace utils;

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
        static void ascii_ppm(Image& img, OutputSettings& os, std::string target);

        /*!
         * Print image in binary.
         *
         * @param img Image to be printed
         * @param os Output settings
         * @param target Target folder
         */
        static void binary_ppm(Image& img, OutputSettings& os, std::string target);
};

#endif /* _PRINTER_H_ */

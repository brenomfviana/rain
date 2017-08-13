#ifndef _PRINTER_H_
#define _PRINTER_H_

#include "image/image.h"

/*!
 * .
 */
class Printer {

    public:
        /*!
         * .
         */
        static void print(Image& img, std::string targetFolder);

    private:
        /*!
         * .
         */
        static void asciiPPM(Image& img, std::string targetFolder);

        /*!
         * .
         */
        static void binaryPPM(Image& img, std::string targetFolder);
};

#endif

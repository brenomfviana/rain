#include <iostream>
#include <fstream>
#include "image/image.h"
#include "printer/printer.h"
#include "printer/image_file_formats.h"

void Printer::print(Image& img, std::string targetFolder) {
    // Check image file format
    if (img.fileFormat == PPM) {
        // Check codification
        if (img.codification == ASCII) {
            asciiPPM(img, targetFolder);
        } else if (img.codification == BINARY) {
            binaryPPM(img, targetFolder);
        }
    } else {
        // ERROR
    }
}

void Printer::asciiPPM(Image& img, std::string targetFolder) {
    // Create image file
    std::ofstream outfile(targetFolder + img.name);
    // PPM header
    outfile << "P3" << std::endl;
    outfile << img.width << " " << img.height << std::endl;
    outfile << "255" << std::endl;
    // Print image
    for (unsigned int row = 0; row < img.height; row++) {
        for(unsigned int col = 0; col < img.width; col++) {
            outfile << (int) ((unsigned char) img.pixels[(row * img.width * 3) + (col * 3)]) << " "
                    << (int) ((unsigned char) img.pixels[(row * img.width * 3) + (col * 3) + 1]) << " "
                    << (int) ((unsigned char) img.pixels[(row * img.width * 3) + (col * 3) + 2]) << std::endl;
        }
    }
    outfile.close();
}

void Printer::binaryPPM(Image& img, std::string targetFolder) {
    // Create image file
    std::ofstream outfile(targetFolder + img.name, std::ofstream::binary);
    // PPM header
    outfile << "P6" << std::endl;
    outfile << img.width << " " << img.height << std::endl;
    outfile << "255" << std::endl;
    // Print image
    outfile.write(img.pixels, img.width * img.height * 3);
    outfile.close();
}

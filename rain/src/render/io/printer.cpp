#include "render/io/printer.h"

void Printer::print(Image& img, OutputSettings& os, std::string target) {
    // Check image file format
    if (os.file_format == OutputSettings::PPM) {
        // Check codification
        if (os.codification == OutputSettings::ASCII) {
            ascii_ppm(img, os, target);
        } else if (os.codification == OutputSettings::BINARY) {
            binary_ppm(img, os, target);
        } else {
            // ERROR
            throw "Invalid codification!";
        }
    } else {
        // ERROR
        throw "Invalid format!";
    }
}

void Printer::ascii_ppm(Image& img, OutputSettings& os, std::string target) {
    // Create image file
    std::ofstream outfile(target + os.name);
    // PPM header
    outfile << "P3" << std::endl;
    outfile << os.width << " " << os.height << std::endl;
    outfile << "255" << std::endl;
    // Print image
    for (unsigned int row = 0; row < os.height; row++) {
        for(unsigned int col = 0; col < os.width; col++) {
            outfile << (int) ((unsigned char) img.pixels[(row * img.width * 3) + (col * 3)]) << " "
                    << (int) ((unsigned char) img.pixels[(row * img.width * 3) + (col * 3) + 1]) << " "
                    << (int) ((unsigned char) img.pixels[(row * img.width * 3) + (col * 3) + 2]) << std::endl;
        }
    }
    outfile.close();
}

void Printer::binary_ppm(Image& img, OutputSettings& os, std::string target) {
    // Create image file
    std::ofstream outfile(target + os.name, std::ofstream::binary);
    // PPM header
    outfile << "P6" << std::endl;
    outfile << os.width << " " << os.height << std::endl;
    outfile << "255" << std::endl;
    // Print image
    outfile.write(img.pixels, img.width * img.height * 3);
    outfile.close();
}

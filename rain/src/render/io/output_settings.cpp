#include "render/io/output_settings.h"

OutputSettings::OutputSettings(std::string name, ImageFileFormats file_format,
    Codifications codification, int width, int height) {
    this->name = name;
    this->file_format = file_format;
    this->codification = codification;
    this->width = width;
    this->height = height;
}

OutputSettings::~OutputSettings() {
    /* empty */
}

OutputSettings::ImageFileFormats OutputSettings::get_image_file_format(std::string str) {
    // Check image file format
    if (str.find("PPM") == 0) {
        return PPM;
    } else {
        // ERROR
        throw "Invalid image file format!";
    }
}

OutputSettings::Codifications OutputSettings::get_codification(std::string str) {
    // Check file format
    if (str.find("ascii") == 0) {
        return ASCII;
    } else if (str.find("binary") == 0) {
        return BINARY;
    } else {
        // ERROR
        throw "Invalid codification!";
    }
}

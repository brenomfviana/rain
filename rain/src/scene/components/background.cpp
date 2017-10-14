#include "scene/components/background.h"

Background::Background() {
    this->upper_left  = RGB();
    this->lower_left  = RGB();
    this->upper_right = RGB();
    this->lower_right = RGB();
}

Background::Background(const RGB color) {
    this->upper_left  = color;
    this->lower_left  = color;
    this->upper_right = color;
    this->lower_right = color;
}

Background::Background(const RGB c1, const RGB c2, const bool orientation) {
    // Check orientation
    if (orientation) {
        this->upper_left  = c1;
        this->lower_left  = c2;
        this->upper_right = c1;
        this->lower_right = c2;
    } else {
        this->upper_left  = c1;
        this->lower_left  = c1;
        this->upper_right = c2;
        this->lower_right = c2;
    }
}

Background::Background(const RGB upper_left, const RGB lower_left,
                       const RGB upper_right, const RGB lower_right) {
    this->upper_left  =  upper_left;
    this->lower_left  =  lower_left;
    this->upper_right = upper_right;
    this->lower_right = lower_right;
}

Background::~Background() {
    /* empty */
}

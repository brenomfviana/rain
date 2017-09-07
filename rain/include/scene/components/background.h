#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_

#include "utils/vec3.h"

/*!
 * This class represents a background of a scene.
 */
class Background {

    public:
        // Upper left corner
        RGB upperLeft;
        // Lower left corner
        RGB lowerLeft;
        // Upper right corner
        RGB upperRight;
        // Lower right corner
        RGB lowerRight;

        /*!
         * Background empty constructor (black background).
         */
        Background() {
            upperLeft = RGB(0, 0, 0);
            lowerLeft = RGB(0, 0, 0);
            upperRight = RGB(0, 0, 0);
            lowerRight = RGB(0, 0, 0);
        }

        /*!
         * Single-color background constructor.
         *
         * @param color_ Color
         */
        Background(RGB color_) :
            upperLeft(color_),
            lowerLeft(color_),
            upperRight(color_),
            lowerRight(color_) { /* empty */ }

        /*!
         * Two-color background constructor. Need to choose orientation, true to
         * vertical, and false to horizontal. Vertical top=c1_ and bottom=c2_.
         * Horizontal left=c1_ and right=c2_.
         *
         * @param c1 First color
         * @param c2 Second color
         * @param orientation_ Orientation
         */
        Background(RGB c1_, RGB c2_, bool orientation_) {
            // Check orientation
            if (orientation_) {
                upperLeft = c1_;
                lowerLeft = c2_;
                upperRight = c1_;
                lowerRight = c2_;
            } else {
                upperLeft = c1_;
                lowerLeft = c1_;
                upperRight = c2_;
                lowerRight = c2_;
            }
        }

        /*!
         * Four-color background constructor. Choose a color for each corner.
         *
         * @param upperLeft_ Upper left corner color
         * @param lowerLeft_ Lower left corner color
         * @param upperRight_ Upper right corner color
         * @param lowerRight_ Lower right corner color
         */
        Background(RGB upperLeft_, RGB lowerLeft_,
            RGB upperRight_, RGB lowerRight_) :
            upperLeft(upperLeft_),
            lowerLeft(lowerLeft_),
            upperRight(upperRight_),
            lowerRight(lowerRight_) { /* empty */ }
};

#endif

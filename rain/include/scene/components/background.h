#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_

#include "vec3.h"

using namespace utils;

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
         * @param color Color
         */
        Background(RGB color) :
            upperLeft(color), lowerLeft(color),
            upperRight(color), lowerRight(color)
                { /* empty */ }

        /*!
         * Two-color background constructor. Need to choose orientation, true to
         * vertical, and false to horizontal. Vertical top=c1 and bottom=c2.
         * Horizontal left=c1 and right=c2.
         *
         * @param c1 First color
         * @param c2 Second color
         * @param orientation Orientation
         */
        Background(RGB c1, RGB c2, bool orientation) {
            // Check orientation
            if (orientation) {
                upperLeft = c1;
                lowerLeft = c2;
                upperRight = c1;
                lowerRight = c2;
            } else {
                upperLeft = c1;
                lowerLeft = c1;
                upperRight = c2;
                lowerRight = c2;
            }
        }

        /*!
         * Four-color background constructor. Choose a color for each corner.
         *
         * @param upperLeft Upper left corner color
         * @param lowerLeft Lower left corner color
         * @param upperRight Upper right corner color
         * @param lowerRight Lower right corner color
         */
        Background(RGB upperLeft, RGB lowerLeft,
                RGB upperRight, RGB lowerRight) :
            upperLeft(upperLeft), lowerLeft(lowerLeft),
            upperRight(upperRight), lowerRight(lowerRight)
                { /* empty */ }
};

#endif /* _BACKGROUND_H_ */

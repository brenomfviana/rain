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
         * Background constructor.
         *
         * @param upperLeft_ Upper left corner
         * @param lowerLeft_ Lower left corner
         * @param upperRight_ Upper right corner
         * @param lowerRight_ Lower right corner
         */
        Background(RGB upperLeft_, RGB lowerLeft_, RGB upperRight_, RGB lowerRight_) :
            upperLeft(upperLeft_), lowerLeft(lowerLeft_), upperRight(upperRight_),
            lowerRight(lowerRight_) { /* empty */ }
};

#endif

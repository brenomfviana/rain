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
        RGB upper_left;
        // Lower left corner
        RGB lower_left;
        // Upper right corner
        RGB upper_right;
        // Lower right corner
        RGB lower_right;

        /*!
         * Background empty constructor (black background).
         */
        Background();

        /*!
         * Single-color background constructor.
         *
         * @param color Color
         */
        Background(const RGB color);

        /*!
         * Two-color background constructor. Need to choose orientation, true to
         * vertical, and false to horizontal. Vertical top=c1 and bottom=c2.
         * Horizontal left=c1 and right=c2.
         *
         * @param c1 First color
         * @param c2 Second color
         * @param orientation Orientation
         */
        Background(const RGB c1, const RGB c2, const bool orientation);

        /*!
         * Four-color background constructor. Choose a color for each corner.
         *
         * @param upper_left Upper left corner color
         * @param lower_left Lower left corner color
         * @param upper_right Upper right corner color
         * @param lower_right Lower right corner color
         */
        Background(const RGB upper_left, const RGB lower_left,
                   const RGB upper_right, const RGB lower_right);

        ~Background();
};

#endif /* _BACKGROUND_H_ */

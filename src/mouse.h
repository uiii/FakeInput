#ifndef FI_MOUSE_H
#define FI_MOUSE_H

#include "config.h"

namespace FakeInput
{
    /** Represents mouse device.
     *
     * Allows you to move the cursor to the required position.
     * Or simulate mouse button press.
     */
    class Mouse
    {
    public:
        /** Mouse button which can be pressed or released */
        enum Button {
            LEFT = 0,
            MIDDLE = 1,
            RIGHT = 2
        };

        /** Moves mouse cursor in direction.
         *
         * @param xDirection
         *     Direction in pixels on X-axis.
         * @param yDirection
         *     Direction in pixels on Y-axis.
         */
        static void move(int xDirection, int yDirection);

        /** Moves mouse cursor to the specified position.
         *
         * @param x
         *     X coordinate of the position.
         * @param y
         *     Y coordinate of the position.
         */
        static void moveTo(int x, int y);

        /** Simulates mouse button press.
         *
         * @param button
         *     Button to be pressed
         */
        static void pressButton(Button button);

        /** Simulates mouse button release.
         *
         * @param button
         *     Button to be released
         */
        static void releaseButton(Button button);

        /** Simulates wheel up move */
        static void wheelUp();

        /** Simulates wheel up down */
        static void wheelDown();
    };
}

#endif

#ifndef FI_MOUSE_H
#define FI_MOUSE_H

#include "config.h"

#ifdef UNIX
    #include <X11/Xlib.h>
#elif WIN32
    #include <windows.h>
#endif

namespace wc
{
    /** Represents mouse device.
     *
     * Allows you to move the cursor to the required position.
     * Or simulate mouse button press.
     */
    class Mouse
    {
    public:
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

        /** Mouse button which can be pressed or released */
        enum Button {
            LEFT = 1,
            MIDDLE = 2,
            RIGHT = 4,
            WHEEL_UP = 8,
            WHEEL_DOWN = 16
        };

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

        /** Returns bit map of pressed buttons
         *
         * @returns
         *     Bit map of pressed buttons
         */
        static int pressedButtons();

    private:
        static int pressedButtons_;

#ifdef UNIX
        static int buttonToX11Button_(Button button);

        static Display* display_;
#endif

#ifdef WIN32
        static INPUT buttonToWinEvent_(Button button, bool press);
#endif
    };
}

#endif

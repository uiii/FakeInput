#ifndef FI_MOUSE_H
#define FI_MOUSE_H

#include "config.h"

#ifdef UNIX
    #include <X11/Xlib.h>
#elif WIN
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

        /** Simulates mouse button press.
         *
         * @param button
         *     Number of button to press.
         *         - 1: left button
         *         - 2: middle button
         *         - 3: right button
         *         - 4: wheel up
         *         - 5: wheel down
         */
        static void pressButton(int button);

        /** Simulates mouse button release.
         *
         * @param button
         *     Number of button to release.
         *         - 1: left button
         *         - 2: middle button
         *         - 3: right button
         *         - 4: wheel up
         *         - 5: wheel down
         */
        static void releaseButton(int button);

    private:
#ifdef UNIX
        static Display* display_;
#endif
    };
}

#endif

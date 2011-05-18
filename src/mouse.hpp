#ifndef FI_MOUSE_HPP
#define FI_MOUSE_HPP

#include "config.hpp"
#include "types.hpp"

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
         *     MouseButton to be pressed
         */
        static void pressButton(MouseButton button);

        /** Simulates mouse button release.
         *
         * @param button
         *     MouseButton to be released
         */
        static void releaseButton(MouseButton button);

        /** Simulates wheel up move */
        static void wheelUp();

        /** Simulates wheel up down */
        static void wheelDown();
    };
}

#endif

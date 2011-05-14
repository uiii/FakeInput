#ifndef FI_KEYBOARD_H
#define FI_KEYBOARD_H

#include "config.h"

#ifdef UNIX
    #include <X11/Xlib.h>
#endif

#include "key.h"

namespace FakeInput
{
    /** Represents keyboard device.
     *
     * Allows you to simulate key press.
     */
    class Keyboard
    {
    public:
        /** Simulate key press.
         *
         * @param key
         *      Key object representing real key to be pressed.
         */
        static void pressKey(Key key);

        /** Simulate key release 
         *
         * @param key
         *      Key object representing real key to be released.
         */
        static void releaseKey(Key key);

    private:
        /** Send fake key event to the system.
         *
         * @param key
         *      Key object representing real key to be pressed.
         * @param isPress
         *      Whether event is press or release.
         * @param flush
         *      Whether to flush output buffer.
         *      If yes, events will be send immediately.
         */
        static void sendKeyEvent_(Key key, bool isPress, bool flush);
    };
}

#endif

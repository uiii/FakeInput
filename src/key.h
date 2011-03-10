#ifndef WC_KEY_H
#define WC_KEY_H

#include "config.h"

#include <X11/Xlib.h>
#include <X11/keysym.h>

#include <string>

namespace wc
{
    /** Represents real keyboard button.
     */
    class Key
    {
    public:
        /** Key constructor.
         *
         * Creates key representing no real key.
         */
        Key();

        /** Key constructor.
         *
         * Creates key from keycode from given X key event.
         *
         * @param event
         *     XKeyEvent (Xlib key event) containing keycode.
         */
        Key(XEvent* event);

        /** Key constructor.
         *
         * Creates key from the name of the key.
         *
         * @param keyName
         *     The name of the key.
         *     Key name can be obtained from X11/keysymdef.h
         *     file in Xlib sources by removing the XK_ prefix from
         *     each name.
         */
        Key(const std::string& keyName);

        /** Gives the code of the key.
         *
         * @returns
         *     Code of the key.
         */
        unsigned int code();

        /** Gives the KeySym object representing the key.
         *
         * @returns
         *     KeySym representing the key.
         */
        KeySym keysym();

        /** Gives the name of the key.
         *
         * @returns
         *     The name of the key.
         */
        const std::string& name();

    private:
        unsigned int code_;
        KeySym keysym_;
        std::string name_;
    };
}

#endif

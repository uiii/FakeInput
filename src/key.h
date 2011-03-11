#ifndef FI_KEY_H
#define FI_KEY_H

#include "config.h"

#ifdef UNIX
    #include <X11/Xlib.h>
    #include <X11/keysym.h>
#endif

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
#ifdef UNIX
        Key(XEvent* event);
#endif

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
#ifdef UNIX
        KeySym keysym();
#endif

        /** Gives the name of the key.
         *
         * @returns
         *     The name of the key.
         */
        const std::string& name();

    private:
        unsigned int code_;
#ifdef UNIX
        KeySym keysym_;
#endif
        std::string name_;
    };
}

#endif

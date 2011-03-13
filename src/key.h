#ifndef FI_KEY_H
#define FI_KEY_H

#include "config.h"

#ifdef UNIX
    #include <X11/Xlib.h>
    #include <X11/keysym.h>
#elif WIN32
    #include <windows.h>
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

#ifdef UNIX
        /** Key constructor.
         *
         * Creates key from keycode from given X key event.
         *
         * @param event
         *     XKeyEvent (Xlib key event) containing keycode.
         *
         * @warning @image html tux.png
         *    Unix-like platform only
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
         *
         * @warning @image html tux.png
         *    Unix-like platform only now. In the future will be
         *    implemented for Windows too.
         */
        Key(const std::string& keyName);
#endif

#ifdef WIN32
        /** Key constructor.
         *
         * Creates key from virtual-key code from given Windows key message.
         *
         * @param message
         *     Windows WM_[SYS]KEY(DOWN|UP) message containing virtual-key code.
         *
         * @warning @image html windows.png
         *    Windows platform only
         */
        Key(MSG* message);

        /** Key constructor.
         *
         * Creates key from the name of the virtual key.
         *
         * @param virtualKey
         *     The virtual-key code.
         *     Virtual-key codes can be obtained from winuser.h header file
         *     or http://msdn.microsoft.com/en-us/library/dd375731 .
         *
         * @warning @image html windows.png
         *    Windows platform only.
         */
        Key(WORD virtualKey);
#endif

        /** Gives the code of the key.
         *
         * @returns
         *     Code of the key.
         */
        unsigned int code() const;

#ifdef UNIX
        /** Gives the KeySym object representing the key.
         *
         * @returns
         *     KeySym representing the key.
         *
         * @warning @image html tux.png
         *    Unix-like platform only
         */
        KeySym keysym() const;
#endif

#ifdef WIN32
        /** Gives the virtual-key code representing the key.
         *
         * @returns
         *     virtual-key code representing the key.
         *
         * @warning @image html windows.png
         *    Windows platform only.
         */
        WORD virtualKey() const;
#endif

        /** Gives the name of the key.
         *
         * @returns
         *     The name of the key.
         */
        const std::string& name() const;

    private:
        unsigned int code_;
#ifdef UNIX
        KeySym keysym_;
#elif WIN32
        WORD virtualKey_;
#endif
        std::string name_;
    };
}

#endif

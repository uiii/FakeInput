#ifndef FI_KEY_UNIX_H
#define FI_KEY_UNIX_H

#include "config.h"

#include <X11/Xlib.h>

#include <string>

#include "key_base.h"
#include "types.h"

namespace FakeInput
{
    /** Represents real keyboard button with appropriate methods on Unix-like platform.
     *
     * @warning @image html tux.png
     *    Unix-like platform only
     */
    class Key_unix : public Key_base
    {
    public:
        /** Key constructor.
         *
         * Creates key representing no real key.
         */
        Key_unix();

        /** Key constructor
         *
         * Creates key according to the key type
         *
         * @param type
         *     KeyType to be created
         *
         * @note @image html note.png
         *     There is no quarantee the key type will act as you expected,
         *     it depends on keyboard layout, language etc., e.g. on Czech
         *     keyboard the @em Key_2 key will print @em 2 or @em ě according to
         *     the set keyboard layout (US or Czech)
         *
         * @note
         *     If there is not appropriate key type, you can use platform dependend
         *     methods Key::fromKeySym (unix) and Key::fromVirtualKey (win)
         */
        Key_unix(KeyType type);
        
        /** Key contructor
         *
         * Creates key from keycode from given X key event.
         *
         * @param event
         *     XKeyEvent (Xlib key event) containing keycode.
         *
         * @warning @image html tux.png
         *    Unix-like platform only
         */
        Key_unix(XEvent* event);

        /** Key contructor
         *
         * Creates key from the KeySym.
         *
         * @param keySym
         *     The KeySym representing appropriate key.
         *     KeySyms can be obtained from X11/keysymdef.h
         *     file in Xlib sources
         *
         * @warning @image html tux.png
         *    Unix-like platform only.
         */
        Key_unix(KeySym keySym);

        /** Gives the KeySym representing the key.
         *
         * @returns
         *     KeySym representing the key.
         *
         * @warning @image html tux.png
         *    Unix-like platform only
         */
        KeySym keysym() const;

    private:
        KeySym keysym_;
    };
}

#endif

#include "key_unix.hpp"

#include <stdexcept>
#include <iostream>

#include "display_unix.hpp"
#include "mapper.hpp"

namespace FakeInput
{
    Key_unix::Key_unix()
    {
        keysym_ = 0;
    }

    Key_unix::Key_unix(KeyType type)
    {
        if(type == Key_NoKey)
        {
            keysym_ = 0;
            code_ = 0;
            name_ = "<no key>";
        }
        else
        {
            keysym_ = translateKey(type);
            code_ = XKeysymToKeycode(display(), keysym_);
            name_ = XKeysymToString(keysym_);
        }
    }

    Key_unix::Key_unix(XEvent* event):
        Key_base()
    {
        if(event->type != KeyPress && event->type != KeyRelease)
            throw std::logic_error("Cannot get key from non-key event");

        code_ = event->xkey.keycode;
        keysym_ = XKeycodeToKeysym(event->xkey.display, code_, 0);
        name_ = XKeysymToString(keysym_);
    }

    Key_unix::Key_unix(KeySym keysym):
        Key_base()
    {
        code_ = XKeysymToKeycode(display(), keysym);
        keysym_ = keysym;
        name_ = XKeysymToString(keysym);
    }

    KeySym Key_unix::keysym() const
    {
        return keysym_;
    }
}

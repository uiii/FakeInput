#include "key.h"

#include <stdexcept>

namespace wc
{
    Key::Key()
    {
        code_ = 0;
        keysym_ = 0;
        name_ = "<no key>";
    }

    Key::Key(XEvent* event)
    {
        if(event->type != KeyPress && event->type != KeyRelease)
            throw std::logic_error("Cannot get key from non-key event");

        code_ = event->xkey.keycode;
        keysym_ = XKeycodeToKeysym(event->xkey.display, code_, 0);
        name_ = XKeysymToString(keysym_);
    }

    Key::Key(const std::string& keyName)
    {
        KeySym keysym = XStringToKeysym(keyName.c_str());
        if(keysym == NoSymbol) throw std::logic_error("Bad key name");

        code_ = XKeysymToKeycode(XOpenDisplay(0), keysym);
        keysym_ = keysym;
        name_ = XKeysymToString(keysym);
    }

    unsigned int Key::code()
    {
        return code_;
    }
    
    KeySym Key::keysym()
    {
        return keysym_;
    }
    
    const std::string& Key::name()
    {
        return name_;
    }
}

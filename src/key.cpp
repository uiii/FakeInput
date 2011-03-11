#include "key.h"

#include <stdexcept>

namespace wc
{
    Key::Key()
    {
        code_ = 0;
        name_ = "<no key>";

#ifdef UNIX
        keysym_ = 0;
#endif
    }

#ifdef UNIX
    Key::Key(XEvent* event)
    {
        if(event->type != KeyPress && event->type != KeyRelease)
            throw std::logic_error("Cannot get key from non-key event");

        code_ = event->xkey.keycode;
        keysym_ = XKeycodeToKeysym(event->xkey.display, code_, 0);
        name_ = XKeysymToString(keysym_);
    }
#endif

    Key::Key(const std::string& keyName)
    {
#ifdef UNIX
        KeySym keysym = XStringToKeysym(keyName.c_str());
        if(keysym == NoSymbol) throw std::logic_error("Bad key name");

        code_ = XKeysymToKeycode(XOpenDisplay(0), keysym);
        keysym_ = keysym;
        name_ = XKeysymToString(keysym);
#endif
    }

    unsigned int Key::code()
    {
        return code_;
    }
    
#ifdef UNIX
    KeySym Key::keysym()
    {
        return keysym_;
    }
#endif
    
    const std::string& Key::name()
    {
        return name_;
    }
}

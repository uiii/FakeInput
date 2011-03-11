#include "keyboard.h"

#ifdef UNIX
    #include <X11/keysym.h>
    #include <X11/extensions/XTest.h>
#endif

#include <iostream>

namespace wc
{
#ifdef UNIX
    Display* Keyboard::display_ = XOpenDisplay(0);
#endif

    void Keyboard::pressKey(wc::Key key)
    {
#ifdef UNIX
        sendKeyEvent_(key, true, true);
#endif
    }

    void Keyboard::releaseKey(wc::Key key)
    {
#ifdef UNIX
        sendKeyEvent_(key, false, true);
#endif
    }

    void Keyboard::sendKeyEvent_(wc::Key key, bool isPress, bool flush)
    {
#ifdef UNIX
        if(key.keysym() == NoSymbol)
        {
            std::cerr << "Cannot send <no key> event";
        }
        else
        {
            XTestFakeKeyEvent(display_, key.code(), isPress, CurrentTime);
         
            if(flush)
            {
                XFlush(display_);
            }
        }
#endif
    }
}

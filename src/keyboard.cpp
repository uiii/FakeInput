#include "keyboard.h"

#include <X11/keysym.h>
#include <X11/extensions/XTest.h>

#include <iostream>

namespace wc
{
    Display* Keyboard::display_ = XOpenDisplay(0);

    void Keyboard::pressKey(wc::Key key)
    {
        sendKeyEvent_(key, true, true);
    }

    void Keyboard::releaseKey(wc::Key key)
    {
        sendKeyEvent_(key, false, true);
    }

    void Keyboard::sendKeyEvent_(wc::Key key, bool isPress, bool flush)
    {
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
    }
}

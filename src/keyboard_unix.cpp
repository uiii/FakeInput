#include "keyboard.hpp"

#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>

#include "display_unix.hpp"

#include <iostream>

namespace FakeInput
{
    void Keyboard::sendKeyEvent_(Key key, bool isPress)
    {
        if(key.keysym() == NoSymbol)
        {
            std::cerr << "Cannot send <no key> event" << std::endl;
        }
        else
        {
            XTestFakeKeyEvent(display(), key.code(), isPress, CurrentTime);
            XFlush(display());
        }
    }
}

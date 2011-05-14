#include "keyboard.h"

#ifdef UNIX
    #include <X11/keysym.h>
    #include <X11/extensions/XTest.h>
#endif

#include "display_unix.h"

#include <iostream>

namespace wc
{
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
#ifdef UNIX
        if(key.keysym() == NoSymbol)
        {
            std::cerr << "Cannot send <no key> event";
        }
        else
        {
            XTestFakeKeyEvent(display(), key.code(), isPress, CurrentTime);
         
            if(flush)
            {
                XFlush(display());
            }
        }
#elif WIN32
        if(key.code() == 0)
        {
            std::cerr << "Cannot send <no key> event";
        }
        else
        {
            INPUT input;
            ZeroMemory(&input, sizeof(INPUT));
            input.type = INPUT_KEYBOARD;
            input.ki.wVk = key.virtualKey();
            input.ki.dwFlags = (isPress) ? 0 : KEYEVENTF_KEYUP;
            SendInput(1, &input, sizeof(INPUT));
        }
#endif
    }
}

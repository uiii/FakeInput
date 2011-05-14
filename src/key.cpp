#include "key.h"

#include <stdexcept>
#include <iostream>

namespace FakeInput
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

    Key::Key(const std::string& keyName)
    {
        KeySym keysym = XStringToKeysym(keyName.c_str());
        if(keysym == NoSymbol) throw std::logic_error("Bad key name");

        code_ = XKeysymToKeycode(XOpenDisplay(0), keysym);
        keysym_ = keysym;
        name_ = XKeysymToString(keysym);
    }
#endif

#ifdef WIN32
    Key::Key(MSG* message)
    {
        switch(message->message)
        {
            case WM_KEYDOWN:
            case WM_KEYUP:
            case WM_SYSKEYDOWN:
            case WM_SYSKEYUP:
                virtualKey_ = message->wParam;
            break;
            default:
                std::logic_error("Cannot get key from non-key message");
            break;
        }

        Key tmpKey(virtualKey_);
        code_ = tmpKey.code_;
        name_ = tmpKey.name_;
    }

    Key::Key(WORD virtualKey):
        virtualKey_(virtualKey)
    {
        code_ = MapVirtualKey(virtualKey, MAPVK_VK_TO_VSC);
        LONG lParam = code_;
        switch (virtualKey)
        {
            case VK_LEFT: case VK_UP: case VK_RIGHT: case VK_DOWN: // arrow keys
            case VK_PRIOR: case VK_NEXT: // page up and page down
            case VK_END: case VK_HOME:
            case VK_INSERT: case VK_DELETE:
            case VK_DIVIDE: // numpad slash
            case VK_NUMLOCK:
            {
                lParam |= 0x100; // set extended bit
                break;
            }
        }

        char name[128];
        if(GetKeyNameText(lParam << 16, name, 128))
        {
            name_ = std::string(name);
        }
        else
        {
            std::cerr << "Cannot get key name";
            name_ = "<unknown key>";
        }
    }
#endif

    unsigned int Key::code() const
    {
        return code_;
    }
    
#ifdef UNIX
    KeySym Key::keysym() const
    {
        return keysym_;
    }
#elif WIN32
    WORD Key::virtualKey() const
    {
        return virtualKey_;
    }
#endif
    
    const std::string& Key::name() const
    {
        return name_;
    }
}

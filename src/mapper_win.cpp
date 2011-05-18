#include "mapper.hpp"

#include <windows.h>

namespace FakeInput
{
    static long buttonTable[] = {
        MOUSEEVENTF_LEFTDOWN, // Mouse::LEFT
        MOUSEEVENTF_MIDDLEDOWN, // Mouse::MIDDLE
        MOUSEEVENTF_RIGHTDOWN // Mouse::RIGHT
    };

    static long keyTable[] = {
        0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, // A - I
        0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50, 0x51, 0x52, // J - R
        0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, // S - Z

        0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, // 0 - 9

        VK_F1, VK_F2, VK_F3, VK_F4, VK_F5, VK_F6, VK_F7, VK_F8, VK_F9, VK_F10, VK_F11, VK_F12,
        VK_F13, VK_F14, VK_F15, VK_F16, VK_F17, VK_F18, VK_F19, VK_F20, VK_F21, VK_F22, VK_F23, VK_F24,

        VK_ESCAPE,
        VK_SPACE,
        VK_RETURN,
        VK_BACK,
        VK_TAB,

        VK_LSHIFT,
        VK_RSHIFT,
        VK_LCONTROL,
        VK_RCONTROL,
        VK_LMENU,
        VK_RMENU,
        VK_LWIN,
        VK_RWIN,
        VK_APPS,

        VK_CAPITAL,
        VK_NUMLOCK,
        VK_SCROLL,

        VK_SNAPSHOT,
        VK_PAUSE,

        VK_INSERT,
        VK_DELETE,
        VK_PRIOR,
        VK_NEXT,
        VK_HOME,
        VK_END,

        VK_LEFT,
        VK_UP,
        VK_RIGHT,
        VK_DOWN,

        VK_NUMPAD0,
        VK_NUMPAD1,
        VK_NUMPAD2,
        VK_NUMPAD3,
        VK_NUMPAD4,
        VK_NUMPAD5,
        VK_NUMPAD6,
        VK_NUMPAD7,
        VK_NUMPAD8,
        VK_NUMPAD9,

        VK_ADD,
        VK_SUBTRACT,
        VK_MULTIPLY,
        VK_DIVIDE,
        VK_DECIMAL,
        VK_RETURN
    };

    long translateMouseButton(MouseButton button)
    {
        return buttonTable[button];
    }
    
    unsigned long translateKey(KeyType key)
    {
        return keyTable[key];
    }
}

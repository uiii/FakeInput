#include "keyboard.hpp"

#include <windows.h>

#include <iostream>

namespace FakeInput
{
    void Keyboard::sendKeyEvent_(Key key, bool isPress)
    {
        if(key.code() == 0)
        {
            std::cerr << "Cannot send <no key> event" << std::endl;
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
    }
}

#include "keyboard.hpp"

namespace FakeInput
{
    void Keyboard::pressKey(Key key)
    {
        sendKeyEvent_(key, true);
    }

    void Keyboard::releaseKey(Key key)
    {
        sendKeyEvent_(key, false);
    }
}

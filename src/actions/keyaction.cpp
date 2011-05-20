#include "keyaction.hpp"

#include "keyboard.hpp"

namespace FakeInput
{
    KeyAction::KeyAction(KeyActionCallback callback, Key key):
        callback_(callback),
        key_(key)
    {
    }

    Action* KeyAction::clone() const
    {
        return new KeyAction(callback_, key_);
    }

    void KeyAction::send() const
    {
        callback_(key_);
    }

    KeyboardPress::KeyboardPress(Key key):
        KeyAction(Keyboard::pressKey, key)
    {
    }

    KeyboardPress::KeyboardPress(KeyType keyType):
        KeyAction(Keyboard::pressKey, Key(keyType))
    {
    }

    KeyboardRelease::KeyboardRelease(Key key):
        KeyAction(Keyboard::releaseKey, key)
    {
    }

    KeyboardRelease::KeyboardRelease(KeyType keyType):
        KeyAction(Keyboard::releaseKey, Key(keyType))
    {
    }
}

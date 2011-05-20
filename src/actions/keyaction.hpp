#ifndef FI_KEYACTION_HPP
#define FI_KEYACTION_HPP

#include "action.hpp"
#include "key.hpp"

namespace FakeInput
{
    typedef void (*KeyActionCallback) (Key key);

    /** Represent a key action. */
    class KeyAction : public Action
    {
    public:
        /** KeyAction constructor.
         *
         * @param callback
         *     Callback whitch can handle with key.
         * @param key
         *     Key to be handled.
         */
        KeyAction(KeyActionCallback callback, Key key);

        /** Creates new copy of this action.
         *
         * @returns
         *     New copy of this action allocated on heap.
         */
        Action* clone() const;

        /** Performs this action. */
        void send() const;

    private:
        KeyActionCallback callback_;
        Key key_;
    };

    /** Represent a key press action. */
    class KeyboardPress : public KeyAction
    {
    public:
        /** KeyboardPress action constructor.
         *
         * @param key
         *    Key to be pressed.
         */
        KeyboardPress(Key key);

        /** KeyboardPress action constructor.
         *
         * @param keyType
         *    Type of key to be pressed.
         */
        KeyboardPress(KeyType keyType);
    };

    /** Represent a key release action. */
    class KeyboardRelease : public KeyAction
    {
    public:
        /** KeyboardRelease action constructor.
         *
         * @param key
         *    Key to be released.
         */
        KeyboardRelease(Key key);

        /** KeyboardRelease action constructor.
         *
         * @param keyType
         *    Type of key to be released.
         */
        KeyboardRelease(KeyType keyType);
    };
}

#endif

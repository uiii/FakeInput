#ifndef FI_KEY_WIN_H
#define FI_KEY_WIN_H

#include "config.h"

#include <windows.h>

#include <string>

#include "key_base.h"
#include "types.h"

namespace FakeInput
{
    /** Represents real keyboard button with appropriate methods on Windows.
     *
     * @warning @image html windows.png
     *    Windows platform only.
     */
    class Key_win : public Key_base
    {
    public:
        /** Key constructor.
         *
         * Creates key representing no real key.
         */
        Key_win();

        /** Key constructor
         *
         * Creates key according to the key type
         *
         * @param type
         *     KeyType to be created
         *
         * @note @image html note.png
         *     There is no quarantee the key type will act as you expected,
         *     it depends on keyboard layout, language etc., e.g. on Czech
         *     keyboard the @em Key_2 key will print @em 2 or @em ě according to
         *     the set keyboard layout (US or Czech)
         *
         * @note
         *     If there is not appropriate key type, you can use platform dependend
         *     methods Key::fromKeySym (unix) and Key::fromVirtualKey (win)
         */
        Key_win(KeyType type);
                
        /** Key constructor
         *
         * Creates key from virtual-key code from given Windows key message.
         *
         * @param message
         *     Windows WM_[SYS]KEY(DOWN|UP) message containing virtual-key code.
         *
         * @warning @image html windows.png
         *    Windows platform only
         */
        Key_win(MSG* message);

        /** Key constructor
         *
         * Creates key from the name of the virtual key.
         *
         * @param virtualKey
         *     The virtual-key code.
         *     Virtual-key codes can be obtained from winuser.h header file
         *     or http://msdn.microsoft.com/en-us/library/dd375731 .
         *
         * @warning @image html windows.png
         *    Windows platform only.
         */
        Key_win(WORD virtualKey);

        /** Gives the virtual-key code representing the key.
         *
         * @returns
         *     virtual-key code representing the key.
         *
         * @warning @image html windows.png
         *    Windows platform only.
         */
        WORD virtualKey() const;

    private:
        WORD virtualKey_;
    };
}

#endif

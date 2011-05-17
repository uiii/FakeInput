#ifndef FI_KEY_H
#define FI_KEY_H

#include "config.h"

#ifdef UNIX
    #include "key_unix.h"
#elif WIN32
    #include "key_win.h"
#endif

namespace FakeInput
{
#ifdef UNIX
    /** Class representing a real key.
     *
     * @image html tux.png
     * On Unix-like platform derived from Key_unix
     */
    typedef Key_unix Key;
#elif WIN32
    /**
     * @image html windows.png
     * On Windows derived from Key_win
     */
    typedef Key_win Key;
#endif
}

#endif

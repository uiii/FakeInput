#ifndef FI_KEY_HPP
#define FI_KEY_HPP

#include "config.hpp"

#ifdef UNIX
    #include "key_unix.hpp"
#elif WIN32
    #include "key_win.hpp"
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

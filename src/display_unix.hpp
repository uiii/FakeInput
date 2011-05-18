#ifndef FI_DISPLAY_UNIX_HPP
#define FI_DISPLAY_UNIX_HPP

#include "config.hpp"

#include <X11/Xlib.h>

namespace FakeInput
{
    /** Get connection to the X server
     *
     * @warning @image html tux.png
     *    Unix-like platform only
     */
    Display* display();
}

#endif

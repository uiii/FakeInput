#ifndef FI_DISPLAY_UNIX_H
#define FI_DISPLAY_UNIX_H

#include "config.h"

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

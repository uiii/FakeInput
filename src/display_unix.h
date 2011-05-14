#ifndef FI_DISPLAY_UNIX_H
#define FI_DISPLAY_UNIX_H

#include "config.h"

namespace FakeInput
{

#ifdef UNIX
    #include <X11/Xlib.h>

    Display* display();
#endif

}

#endif

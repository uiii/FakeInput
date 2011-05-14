#ifndef FI_DISPLAY_UNIX_H
#define FI_DISPLAY_UNIX_H

#include "config.h"

namespace wc
{

#ifdef UNIX
    #include <X11/Xlib.h>

    Display* display();
#endif

}

#endif

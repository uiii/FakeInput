#include "display_unix.h"

namespace wc
{

#ifdef UNIX
    Display* display()
    {
        static Display* display = XOpenDisplay(0);
        return display;
    }
#endif

}

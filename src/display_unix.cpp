#include "display_unix.h"

namespace FakeInput
{

#ifdef UNIX
    Display* display()
    {
        static Display* display = XOpenDisplay(0);
        return display;
    }
#endif

}

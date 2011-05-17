#include "display_unix.h"

namespace FakeInput
{
    Display* display()
    {
        static Display* display = XOpenDisplay(0);
        return display;
    }
}

#include "display_unix.hpp"

namespace FakeInput
{
    Display* display()
    {
        static Display* display = XOpenDisplay(0);
        return display;
    }
}

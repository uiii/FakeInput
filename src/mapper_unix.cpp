#include "mapper.h"

#include <X11/Xlib.h>

namespace FakeInput
{
    static long trTable[] = {
        Button1, // Mouse::LEFT
        Button2, // Mouse::MIDDLE
        Button3 // Mouse::RIGHT
    };

    long translateMouseButton(Mouse::Button button)
    {
        return trTable[button];
    }
}

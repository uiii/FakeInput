#include "mapper.h"

#include <windows.h>

namespace FakeInput
{
    static long trTable[] = {
        MOUSEEVENTF_LEFTDOWN, // Mouse::LEFT
        MOUSEEVENTF_MIDDLEDOWN, // Mouse::MIDDLE
        MOUSEEVENTF_RIGHTDOWN // Mouse::RIGHT
    };

    long translateMouseButton(Mouse::Button button)
    {
        return trTable[button];
    }
}

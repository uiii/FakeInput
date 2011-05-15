#include "mapper.h"

namespace FakeInput
{
    static long trTable[] = {
        MOUSEEVENF_LEFTDOWN, // Mouse::LEFT
        MOUSEEVENTF_MIDDLEDOWN, // Mouse::MIDDLE
        MOUSEEVENTF_RIGHTDOWN // Mouse::RIGHT
    };

    long translateMouseButton(Mouse::Button button)
    {
        return trTabel[button];
    }
}

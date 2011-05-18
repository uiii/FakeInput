#include "mouse.hpp"

#include <windows.h>

#include "mapper.hpp"
#include "types.hpp"

#define INIT_INPUT(var) \
    INPUT var; \
    ZeroMemory(&var, sizeof(INPUT)); \
    var.type = INPUT_MOUSE;

namespace FakeInput
{
    void Mouse::move(int x, int y)
    {
        INIT_INPUT(input);
        input.mi.dx = x;
        input.mi.dy = y;
        input.mi.dwFlags = MOUSEEVENTF_MOVE;
        SendInput(1, &input, sizeof(INPUT));
    }

    void Mouse::moveTo(int x, int y)
    {
        double screenWidth = GetSystemMetrics(SM_CXSCREEN) - 1; 
        double screenHeight = GetSystemMetrics(SM_CYSCREEN) - 1; 
        double fx = x * (65535.0f / screenWidth);
        double fy = y * (65535.0f / screenHeight);

        INIT_INPUT(input);
        input.mi.dx = (LONG) fx;
        input.mi.dy = (LONG) fy;
        input.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE;
        SendInput(1, &input, sizeof(INPUT));
    }

    void Mouse::pressButton(MouseButton button)
    {
        INIT_INPUT(input);
        input.mi.dwFlags = translateMouseButton(button);

        SendInput(1, &input, sizeof(INPUT));
    }

    void Mouse::releaseButton(MouseButton button)
    {
        INIT_INPUT(input);
        input.mi.dwFlags = translateMouseButton(button) << 1;

        SendInput(1, &input, sizeof(INPUT));
    }

    void Mouse::wheelUp()
    {
        INIT_INPUT(input);
        input.mi.dwFlags = MOUSEEVENTF_WHEEL;
        input.mi.mouseData = WHEEL_DELTA;

        SendInput(1, &input, sizeof(INPUT));
    }

    void Mouse::wheelDown()
    {
        INIT_INPUT(input);
        input.mi.dwFlags = MOUSEEVENTF_WHEEL;
        input.mi.mouseData = -WHEEL_DELTA;

        SendInput(1, &input, sizeof(INPUT));
    }
}

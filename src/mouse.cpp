#include "mouse.h"

#include <cmath>
#include <iostream>

#ifdef UNIX
    #include <X11/extensions/XTest.h>
#endif

namespace wc
{
    int Mouse::pressedButtons_ = 0;

#ifdef UNIX
    Display* Mouse::display_ = XOpenDisplay(0);
#endif

    void Mouse::move(int x, int y)
    {
#ifdef UNIX
        XTestFakeRelativeMotionEvent(display_, x, y, CurrentTime);
        XFlush(display_);
#elif WIN32
        INPUT input;
        ZeroMemory(&input, sizeof(INPUT));
        input.type = INPUT_MOUSE;
        input.mi.dx = x;
        input.mi.dy = y;
        input.mi.dwFlags = MOUSEEVENTF_MOVE;
        SendInput(1, &input, sizeof(INPUT));
#endif
    }

    void Mouse::moveTo(int x, int y)
    {
#ifdef UNIX
        XTestFakeMotionEvent(display_, -1, x, y, CurrentTime);
        XFlush(display_);
#elif WIN32
        double screenWidth = GetSystemMetrics(SM_CXSCREEN) - 1; 
        double screenHeight = GetSystemMetrics(SM_CYSCREEN) - 1; 
        double fx = x * (65535.0f / screenWidth);
        double fy = y * (65535.0f / screenHeight);

        INPUT input;
        ZeroMemory(&input, sizeof(INPUT));
        input.type = INPUT_MOUSE;
        input.mi.dx = (LONG) fx;
        input.mi.dy = (LONG) fy;
        input.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE;
        SendInput(1, &input, sizeof(INPUT));
#endif
    }

    void Mouse::pressButton(Mouse::Button button)
    {
        pressedButtons_ = pressedButtons_ | button;

#ifdef UNIX
        int xButton = buttonToX11Button_(button);
        XTestFakeButtonEvent(display_, xButton, true, CurrentTime);
        XFlush(display_);
#elif WIN32
        INPUT input = buttonToWinEvent_(button, true);
        SendInput(1, &input, sizeof(INPUT));
#endif
    }

    void Mouse::releaseButton(Mouse::Button button)
    {
        pressedButtons_ = pressedButtons_ & ~button;

#ifdef UNIX
        int xButton = buttonToX11Button_(button);
        XTestFakeButtonEvent(display_, xButton, false, CurrentTime);
        XFlush(display_);
#elif WIN32
        INPUT input = buttonToWinEvent_(button, false);
        SendInput(1, &input, sizeof(INPUT));
#endif
    }

    int Mouse::pressedButtons()
    {
        return pressedButtons_;
    }

#ifdef UNIX
    int Mouse::buttonToX11Button_(Button button)
    {
        return std::log(button);
    }
#endif

#ifdef WIN32
    INPUT Mouse::buttonToWinEvent_(Mouse::Button button, bool press)
    {
        INPUT input;
        ZeroMemory(&input, sizeof(INPUT));
        input.type = INPUT_MOUSE;

        switch(button)
        {
            case Mouse::LEFT:
                if(press) input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
                else input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
            break;
            case Mouse::MIDDLE:
                if(press) input.mi.dwFlags = MOUSEEVENTF_MIDDLEDOWN;
                else input.mi.dwFlags = MOUSEEVENTF_MIDDLEUP;
            break;
            case Mouse::RIGHT:
                if(press) input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
                else input.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
            break;
            case Mouse::WHEEL_UP:
                input.mi.dwFlags = MOUSEEVENTF_WHEEL;
                input.mi.mouseData = 1;
            break;
            case Mouse::WHEEL_DOWN:
                input.mi.dwFlags = MOUSEEVENTF_WHEEL;
                input.mi.mouseData = -1;
            break;
            default:
            break;
        }

        /*bool release = ! press;
        if(release && (input.mi.dwFlags != MOUSEEVENTF_WHEEL))
        {
            // Change event to release instead of press.
            // Value of MOUSEEVENTF_*UP constant
            // is double of MOUSEEVENTF_*DOWN constant
            input.mi.dwFlags = input.mi.dwFlags * 2;
        }*/

        return input;
    }
#endif
}

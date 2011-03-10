#include "mouse.h"

#include <X11/extensions/XTest.h>

namespace wc
{
    Display* Mouse::display_ = XOpenDisplay(0);

    void Mouse::move(int x, int y)
    {
        XTestFakeRelativeMotionEvent(display_, x, y, CurrentTime);
        XFlush(display_);
    }

    void Mouse::moveTo(int x, int y)
    {
        XTestFakeMotionEvent(display_, -1, x, y, CurrentTime);
        XFlush(display_);
    }

    void Mouse::pressButton(int button)
    {
        XTestFakeButtonEvent(display_, button, true, CurrentTime);
        XFlush(display_);
    }

    void Mouse::releaseButton(int button)
    {
        XTestFakeButtonEvent(display_, button, false, CurrentTime);
        XFlush(display_);
    }
}

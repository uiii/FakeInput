#include "mouse.h"

#ifdef UNIX
    #include <X11/extensions/XTest.h>
#endif

namespace wc
{
#ifdef UNIX
    Display* Mouse::display_ = XOpenDisplay(0);
#endif

    void Mouse::move(int x, int y)
    {
#ifdef UNIX
        XTestFakeRelativeMotionEvent(display_, x, y, CurrentTime);
        XFlush(display_);
#endif
    }

    void Mouse::moveTo(int x, int y)
    {
#ifdef UNIX
        XTestFakeMotionEvent(display_, -1, x, y, CurrentTime);
        XFlush(display_);
#endif
    }

    void Mouse::pressButton(int button)
    {
#ifdef UNIX
        XTestFakeButtonEvent(display_, button, true, CurrentTime);
        XFlush(display_);
#endif
    }

    void Mouse::releaseButton(int button)
    {
#ifdef UNIX
        XTestFakeButtonEvent(display_, button, false, CurrentTime);
        XFlush(display_);
#endif
    }
}

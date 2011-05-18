#include "mouse.hpp"

#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>

#include "display_unix.hpp"

#include "mapper.hpp"

namespace FakeInput
{
    void Mouse::move(int x, int y)
    {
        XTestFakeRelativeMotionEvent(display(), x, y, CurrentTime);
        XFlush(display());
    }

    void Mouse::moveTo(int x, int y)
    {
        XTestFakeMotionEvent(display(), -1, x, y, CurrentTime);
        XFlush(display());
    }

    void Mouse::pressButton(MouseButton button)
    {
        int xButton = translateMouseButton(button);
        XTestFakeButtonEvent(display(), xButton, true, CurrentTime);
        XFlush(display());
    }

    void Mouse::releaseButton(MouseButton button)
    {
        int xButton = translateMouseButton(button);
        XTestFakeButtonEvent(display(), xButton, false, CurrentTime);
        XFlush(display());
    }

    void Mouse::wheelUp()
    {
        XTestFakeButtonEvent(display(), 4, true, CurrentTime);
        XSync(display(), false);
        XTestFakeButtonEvent(display(), 4, false, CurrentTime);
        XFlush(display());
    }

    void Mouse::wheelDown()
    {
        XTestFakeButtonEvent(display(), 5, true, CurrentTime);
        XSync(display(), false);
        XTestFakeButtonEvent(display(), 5, false, CurrentTime);
        XFlush(display());
    }
}

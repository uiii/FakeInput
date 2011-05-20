#include "mouseaction.hpp"

namespace FakeInput
{
    // -------- MOUSE BUTTONS --------- //
    MouseButtonAction::MouseButtonAction(MouseButtonActionCallback callback, MouseButton button):
        callback_(callback),
        button_(button)
    {
    }

    Action* MouseButtonAction::clone() const
    {
        return new MouseButtonAction(callback_, button_);
    }

    void MouseButtonAction::send() const
    {
        (*callback_)(button_);
    }

    MousePress::MousePress(MouseButton button):
        MouseButtonAction(Mouse::pressButton, button)
    {
    }

    MouseRelease::MouseRelease(MouseButton button):
        MouseButtonAction(Mouse::releaseButton, button)
    {
    }

    // -------- MOUSE MOTION --------- //
    MouseMotionAction::MouseMotionAction(MouseMotionActionCallback callback, int x, int y):
        callback_(callback),
        x_(x),
        y_(y)
    {
    }

    Action* MouseMotionAction::clone() const
    {
        return new MouseMotionAction(callback_, x_, y_);
    }

    void MouseMotionAction::send() const
    {
        callback_(x_, y_);
    }

    MouseRelativeMotion::MouseRelativeMotion(int dx, int dy):
        MouseMotionAction(Mouse::move, dx, dy)
    {
    }

    MouseAbsoluteMotion::MouseAbsoluteMotion(int x, int y):
        MouseMotionAction(Mouse::moveTo, x, y)
    {
    }

    // -------- MOUSE WHEEL --------- //
    MouseWheelAction::MouseWheelAction(MouseWheelActionCallback callback):
        callback_(callback)
    {
    }

    Action* MouseWheelAction::clone() const
    {
        return new MouseWheelAction(callback_);
    }

    void MouseWheelAction::send() const
    {
        callback_();
    }

    MouseWheelUp::MouseWheelUp():
        MouseWheelAction(Mouse::wheelUp)
    {
    }

    MouseWheelDown::MouseWheelDown():
        MouseWheelAction(Mouse::wheelDown)
    {
    }
}

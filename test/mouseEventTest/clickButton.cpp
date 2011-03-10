#include "clickButton.h"

ClickButton::ClickButton(QWidget* parent):
    QPushButton("Click me!", parent)
{
}

void ClickButton::mousePressEvent(QMouseEvent* event)
{
    switch(event->button())
    {
        case Qt::LeftButton:
            setText("LEFT click");
            break;
        case Qt::RightButton:
            setText("RIGHT click");
            break;
        default:
            break;
    }
}

void ClickButton::mouseReleaseEvent(QMouseEvent* event)
{
    setText("Click me!");
}

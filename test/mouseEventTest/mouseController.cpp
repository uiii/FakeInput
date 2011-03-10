#include "mouseController.h"

#include <QApplication>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

#include <iostream>

#include "clickButton.h"

#include "mouse.h"

MouseController::MouseController():
    QDialog(0)//, Qt::Tool | Qt::WindowStaysOnTopHint | Qt::X11BypassWindowManagerHint)
{
    QVBoxLayout* vbox = new QVBoxLayout;

    QLabel* instructions = new QLabel(
            "Move mouse with arrow keys\nLeft click - x\nRight click - c",
            this);

    ClickButton* clickButton = new ClickButton(this);
    clickButton->setFocusPolicy(Qt::NoFocus);
    QPushButton* quitButton = new QPushButton("Close", this);
    quitButton->setFocusPolicy(Qt::NoFocus);

    vbox->addWidget(instructions);
    vbox->addWidget(clickButton);
    vbox->addWidget(quitButton);

    setLayout(vbox);

    connect(quitButton, SIGNAL(clicked()), qApp, SLOT(quit()));
}

void MouseController::keyPressEvent(QKeyEvent* event)
{
    switch(event->key())
    {
        case Qt::Key_Left:
            wc::Mouse::move(-5, 0);
            break;
        case Qt::Key_Right:
            wc::Mouse::move(5, 0);
            break;
        case Qt::Key_Up:
            wc::Mouse::move(0, -5);
            break;
        case Qt::Key_Down:
            wc::Mouse::move(0, 5);
            break;
        case Qt::Key_X:
            wc::Mouse::pressButton(1);
            break;
        case Qt::Key_C:
            wc::Mouse::pressButton(3);
            break;
        default:
            break;
    }
}

void MouseController::keyReleaseEvent(QKeyEvent* event)
{
    switch(event->key())
    {
        case Qt::Key_X:
            wc::Mouse::releaseButton(1);
            break;
        case Qt::Key_C:
            wc::Mouse::releaseButton(3);
            break;
        default:
            break;
    }
}

bool MouseController::x11Event(XEvent* event)
{
    if(event->type == FocusOut)
    {
        wc::Mouse::releaseButton(1);
        wc::Mouse::releaseButton(3);
    }

    return false;
}

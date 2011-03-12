#include "mouseController.h"

#include <QApplication>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>

#include <iostream>

#include "clickButton.h"

#include "mouse.h"

using wc::Mouse;

MouseController::MouseController():
    QDialog(0)
{
    QVBoxLayout* vbox = new QVBoxLayout();

    QLabel* instructions = new QLabel(
            "Move mouse with arrow keys\nLeft click - x\nRight click - c",
            this);

    ClickButton* clickButton = new ClickButton(this);
    clickButton->setFocusPolicy(Qt::NoFocus);
    QPushButton* quitButton = new QPushButton("Close", this);
    quitButton->setFocusPolicy(Qt::NoFocus);

    QLabel* xLabel = new QLabel("x: ", this);
    QLabel* yLabel = new QLabel("y: ", this);
    xPos_ = new QSpinBox(this);
    xPos_->setFocusPolicy(Qt::NoFocus);
    xPos_->setSingleStep(50);
    xPos_->setMaximum(10000);
    yPos_ = new QSpinBox(this);
    yPos_->setFocusPolicy(Qt::NoFocus);
    yPos_->setSingleStep(50);
    yPos_->setMaximum(10000);
    QPushButton* setMousePosButton = new QPushButton("Set mouse position", this);
    setMousePosButton->setFocusPolicy(Qt::NoFocus);
    setMousePosButton->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);

    QGridLayout* grid = new QGridLayout();
    grid->addWidget(xLabel, 0, 0);
    grid->addWidget(xPos_, 0, 1);
    grid->addWidget(yLabel, 1, 0);
    grid->addWidget(yPos_, 1, 1);
    grid->addWidget(setMousePosButton, 0, 2, 2, 1);

    vbox->addWidget(instructions);
    vbox->addLayout(grid);
    vbox->addWidget(clickButton);
    vbox->addWidget(quitButton);

    setLayout(vbox);

    connect(setMousePosButton, SIGNAL(clicked()), this, SLOT(setMousePos()));
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
            wc::Mouse::pressButton(Mouse::LEFT);
            break;
        case Qt::Key_C:
            wc::Mouse::pressButton(Mouse::RIGHT);
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
            wc::Mouse::releaseButton(Mouse::LEFT);
            break;
        case Qt::Key_C:
            wc::Mouse::releaseButton(Mouse::RIGHT);
            break;
        default:
            break;
    }
}

void MouseController::setMousePos()
{
    if(xPos_->text() != "" && yPos_->text() != "")
    {
        int x = xPos_->text().toInt();
        int y = yPos_->text().toInt();

        wc::Mouse::moveTo(x, y);
    }
}

#ifdef UNIX
bool MouseController::x11Event(XEvent* event)
{
    if(event->type == FocusOut)
    {
        wc::Mouse::releaseButton(Mouse::LEFT);
        wc::Mouse::releaseButton(Mouse::RIGHT);
    }

    return false;
}
#elif WIN32
bool MouseController::winEvent(MSG* message, long* result)
{
    if(message->message == WM_KILLFOCUS)
    {
        if((Mouse::pressedButtons() & Mouse::LEFT) != 0)
        {
            wc::Mouse::releaseButton(Mouse::LEFT);
        }

        if((Mouse::pressedButtons() & Mouse::RIGHT) != 0)
        {
            wc::Mouse::releaseButton(Mouse::RIGHT);
        }
    }

    return false;
}
#endif

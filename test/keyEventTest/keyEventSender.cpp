#include "keyEventSender.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <iostream>

#include "keyboard.h"

Sender::Sender():
    QWidget(0, Qt::WindowStaysOnTopHint
#ifdef UNIX
            | Qt::X11BypassWindowManagerHint
#endif
    )
{
    setFocusPolicy(Qt::NoFocus);
    QVBoxLayout* vbox = new QVBoxLayout(this);
    QPushButton* sendButton = new QPushButton("send key event", this);
    QPushButton* quitButton = new QPushButton("close", this);
    vbox->addWidget(sendButton);
    vbox->addWidget(quitButton);

    setLayout(vbox);

    connect(sendButton, SIGNAL(pressed()), this, SLOT(sendPress()));
    connect(sendButton, SIGNAL(released()), this, SLOT(sendRelease()));
    connect(quitButton, SIGNAL(pressed()), this, SLOT(hide()));

#ifdef UNIX
    display_ = XOpenDisplay(0);
#endif
}

Sender::~Sender() {}

#ifdef WIN32
bool Sender::winEvent(MSG* message, long* result)
{
    if(message->message == WM_ACTIVATE)
    {
        focusWindow_ = (HWND)message->lParam;
    }

    return false;
}
#endif

void Sender::setKey(wc::Key key)
{
    key_ = key;
}

void Sender::sendPress()
{
#ifdef WIN32
    SetActiveWindow(focusWindow_);
#endif
    wc::Keyboard::pressKey(key_);
}

void Sender::sendRelease()
{
#ifdef WIN32
    SetActiveWindow(focusWindow_);
#endif
    wc::Keyboard::releaseKey(key_);
}

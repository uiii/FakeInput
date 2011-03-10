#include "keyEventSender.h"

#include <QVBoxLayout>
#include <QPushButton>

#include <X11/Xlib.h>

#include "keyboard.h"

Sender::Sender():
    QDialog(0, Qt::Tool | Qt::WindowStaysOnTopHint | Qt::X11BypassWindowManagerHint)
{
    QVBoxLayout* vbox = new QVBoxLayout(this);
    QPushButton* sendButton = new QPushButton("send key event", this);
    QPushButton* quitButton = new QPushButton("close", this);
    vbox->addWidget(sendButton);
    vbox->addWidget(quitButton);

    setLayout(vbox);

    connect(sendButton, SIGNAL(pressed()), this, SLOT(sendPress()));
    connect(sendButton, SIGNAL(released()), this, SLOT(sendRelease()));
    connect(quitButton, SIGNAL(pressed()), this, SLOT(hide()));

    display_ = XOpenDisplay(0);
}

Sender::~Sender() {}

void Sender::setKey(wc::Key key)
{
    key_ = key;
}

void Sender::sendPress()
{
    wc::Keyboard::pressKey(key_);
}

void Sender::sendRelease()
{
    wc::Keyboard::releaseKey(key_);
}

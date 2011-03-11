#include "keyEventGrabber.h"

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

#include <iostream>

#include "keyEventSender.h"

Grabber::Grabber():
    QWidget(0),
    isReady_(false),
    isGrabbing_(false)
{
    QVBoxLayout *vbox = new QVBoxLayout(this);

    sender_ = new Sender();

    keyName_ = new QLabel("key name: <no key>", this);
    grabButton_ = new QPushButton("grab key event", this);
    grabButton_->setFocusPolicy(Qt::NoFocus);
    sendButton_ = new QPushButton("send key event", this);
    sendButton_->setFocusPolicy(Qt::NoFocus);

    vbox->addWidget(keyName_);
    vbox->addWidget(grabButton_);
    vbox->addWidget(sendButton_);

    setLayout(vbox);

    connect(grabButton_, SIGNAL(clicked()), this, SLOT(grabKeyEvent()));
    connect(sendButton_, SIGNAL(pressed()), sender_, SLOT(show()));

#ifdef UNIX
    display_ = XOpenDisplay(0);
#endif

    setLayout(vbox);
}

Grabber::~Grabber()
{
}

#ifdef UNIX
bool Grabber::x11Event(XEvent* event)
{
    if(isReady_ == false)
    {
        if(event->type == FocusIn)
        {
            display_ = event->xfocus.display;
            window_ = &(event->xfocus.window);
            
            isReady_ = true;
        }
    }

    if(isGrabbing_ == true)
    {
        if(event->type == KeyPress || event->type == KeyRelease)
        {
            key_ = wc::Key(event);
            sender_->setKey(key_);

            keyName_->setText(QString("key name: ") + QString(key_.name().c_str()));

            XUngrabKeyboard(event->xkey.display, CurrentTime);

            isGrabbing_ = false;
        }
    }

    return false;
}
#endif

void Grabber::grabKeyEvent()
{
    if(isReady_ == true)
    {
#ifdef UNIX
        XGrabKeyboard(display_, *window_, false, GrabModeAsync, GrabModeAsync, CurrentTime);
        isGrabbing_ = true;
#endif
    }
    else
    {
        std::cerr << "Canot grab keyboard" << std::endl;
    }
}

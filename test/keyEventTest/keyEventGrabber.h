#ifndef TEST_GRABBER_H
#define TEST_GRABBER_H

#include <QWidget>

#include <X11/Xlib.h>

#include "key.h"

class QLabel;
class QPushButton;

class Sender;

class Grabber : public QWidget
{
    Q_OBJECT

public:
    Grabber();
    virtual ~Grabber();

    bool x11Event(XEvent* event);

public slots:
    void grabKeyEvent();

private:
    Display* display_;
    Window* window_;

    bool isReady_;
    bool isGrabbing_;

    QLabel* keyName_;

    QPushButton* grabButton_;
    QPushButton* sendButton_;

    wc::Key key_;

    Sender* sender_;
};

#endif

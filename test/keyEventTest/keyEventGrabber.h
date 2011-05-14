#ifndef TEST_GRABBER_H
#define TEST_GRABBER_H

#include <QWidget>

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

#ifdef UNIX
    bool x11Event(XEvent* event);
#elif WIN32
    bool winEvent(MSG* message, long* result);
#endif

public slots:
    void grabKeyEvent();

private:
#ifdef UNIX
    Display* display_;
    Window* window_;
#endif

    bool isReady_;
    bool isGrabbing_;

    QLabel* keyName_;

    QPushButton* grabButton_;
    QPushButton* sendButton_;

    FakeInput::Key key_;

    Sender* sender_;
};

#endif

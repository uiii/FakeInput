#ifndef TEST_SENDER_HPP
#define TEST_SENDER_HPP

#include <QDialog>

#include "key.hpp"

class Sender : public QWidget
{
    Q_OBJECT

public:
    Sender();
    virtual ~Sender();

    void setKey(FakeInput::Key key);

#ifdef WIN32
    bool winEvent(MSG* message, long* result);
#endif

public slots:
    void sendPress();
    void sendRelease();

private:
#ifdef UNIX
    Display* display_;
#elif WIN32
    HWND focusWindow_;
#endif

    FakeInput::Key key_;
};

#endif

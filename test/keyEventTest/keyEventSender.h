#ifndef TEST_SENDER
#define TEST_SENDER

#include <QDialog>

#include "key.h"

class Sender : public QWidget
{
    Q_OBJECT

public:
    Sender();
    virtual ~Sender();

    void setKey(wc::Key key);

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

    wc::Key key_;
};

#endif

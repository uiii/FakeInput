#ifndef TEST_SENDER
#define TEST_SENDER

#include <QDialog>

#include <X11/Xlib.h>

#include "key.h"

class Sender : public QDialog
{
    Q_OBJECT

public:
    Sender();
    virtual ~Sender();

    void setKey(wc::Key key);

public slots:
    void sendPress();
    void sendRelease();

private:
    Display* display_;

    wc::Key key_;
};

#endif

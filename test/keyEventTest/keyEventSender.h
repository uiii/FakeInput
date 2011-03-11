#ifndef TEST_SENDER
#define TEST_SENDER

#include <QDialog>

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
#ifdef UNIX
    Display* display_;
#endif

    wc::Key key_;
};

#endif

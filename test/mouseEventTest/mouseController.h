#ifndef TEST_MOUSECONTROLLER_H
#define TEST_MOUSECONTROLLER_H

#include "config.h"

#include <QDialog>

class MouseController : public QDialog
{
public:
    MouseController();

    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);

#ifdef UNIX
    bool x11Event(XEvent* event);
#endif

};


#endif

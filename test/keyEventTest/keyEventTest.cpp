#include <QApplication>

#include "keyEventGrabber.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    Grabber grabber;
    grabber.show();
    return app.exec();
}

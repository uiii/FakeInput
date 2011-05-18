#include <QApplication>

#include "keyEventGrabber.hpp"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    Grabber grabber;
    grabber.show();
    return app.exec();
}

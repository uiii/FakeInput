#include <QApplication>

#include "mouseController.hpp"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    MouseController mc;
    mc.show();
    return app.exec();
}

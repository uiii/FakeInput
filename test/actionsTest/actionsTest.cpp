#include <QApplication>

#include "actionsController.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ActionsController ac;
    ac.show();

    return a.exec();
}

#include <QApplication>

#include "executer.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    Executer exec;
    exec.show();
    return app.exec();
}

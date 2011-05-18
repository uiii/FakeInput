#include <QApplication>

#include "executer.hpp"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    Executer exec;
    exec.show();
    return app.exec();
}

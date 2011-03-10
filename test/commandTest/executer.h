#ifndef TEST_EXEC
#define TEST_EXEC

#include <QWidget>

class QLineEdit;

class Executer : public QWidget
{
    Q_OBJECT

public:
    Executer();
    virtual ~Executer();

public slots:
    void runCommand();

private:
    QLineEdit* cmd_;
};

#endif

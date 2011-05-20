#ifndef TEST_ACTIONSCONTROLLER_HPP
#define TEST_ACTIONSCONTROLLER_HPP

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "actionForm.hpp"

#include "actions/actionsequence.hpp"

class ActionsController : public QDialog
{
    Q_OBJECT

public:
    ActionsController();

public slots:
    void addAction();
    void sendActionSequence();

private:
    ActionForm* form_;
    QVBoxLayout* actionVBox_;

    FakeInput::ActionSequence actionSequence_;
};

#endif

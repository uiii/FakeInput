#ifndef TEST_ACTIONFORM_HPP
#define TEST_ACTIONFORM_HPP

#include <QWidget>
#include <QComboBox>
#include <QSpinBox>
#include <QLineEdit>
#include <QString>

#include "actions/actionsequence.hpp"

/*namespace FakeInput
{
    class ActionSequence; // fwd declaration
}*/

class ActionForm : public QWidget
{
    Q_OBJECT

public:
    ActionForm(QWidget* parent);

    QString addActionToSequence(FakeInput::ActionSequence& sequence);

private:
    QComboBox* actionType_;

    QComboBox* keySelector_;
    QComboBox* mouseButtonSelector_;
    QSpinBox* mouseMotionX_;
    QSpinBox* mouseMotionY_;
    QComboBox* mouseWheelDirection_;
    QLineEdit* command_;
    QSpinBox* waitTime_;
};

#endif

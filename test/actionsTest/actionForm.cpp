#include "actionForm.hpp"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QStackedWidget>

#include "keyboard.hpp"
#include "mouse.hpp"
#include "system.hpp"

Q_DECLARE_METATYPE(FakeInput::KeyType);
Q_DECLARE_METATYPE(FakeInput::MouseButton);
Q_ENUMS(FakeInput::KeyType);
Q_ENUMS(FakeInput::MouseButton);

ActionForm::ActionForm(QWidget* parent):
    QWidget(parent)
{
    QVBoxLayout* vbox = new QVBoxLayout(this);

    actionType_ = new QComboBox(this);
    actionType_->addItem("press & release key");
    actionType_->addItem("click mouse button");
    actionType_->addItem("move mouse");
    actionType_->addItem("rotate wheel");
    actionType_->addItem("run command");
    actionType_->addItem("wait");
    
    QWidget* keyOptions_ = new QWidget();
    QWidget* mouseButtonOptions_ = new QWidget();
    QWidget* mouseMotionOptions_ = new QWidget();
    QWidget* mouseWheelOptions_ = new QWidget();
    QWidget* commandOptions_ = new QWidget();
    QWidget* waitOptions_ = new QWidget();

    QHBoxLayout* keyHBox = new QHBoxLayout();
    QHBoxLayout* mouseButtonHBox = new QHBoxLayout();
    QHBoxLayout* mouseMotionHBox = new QHBoxLayout();
    QHBoxLayout* mouseWheelHBox = new QHBoxLayout();
    QHBoxLayout* commandHBox = new QHBoxLayout();
    QHBoxLayout* waitHBox = new QHBoxLayout();

    keySelector_ = new QComboBox();
    keySelector_->addItem("A", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_A)); 	
	keySelector_->addItem("B", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_B)); 	
	keySelector_->addItem("C", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_C)); 	
	keySelector_->addItem("D", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_D)); 	
	keySelector_->addItem("E", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_E)); 	
	keySelector_->addItem("F", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_F)); 	
	keySelector_->addItem("G", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_G)); 	
	keySelector_->addItem("H", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_H)); 	
	keySelector_->addItem("I", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_I)); 	
	keySelector_->addItem("J", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_J)); 	
	keySelector_->addItem("K", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_K)); 	
	keySelector_->addItem("L", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_L)); 	
	keySelector_->addItem("M", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_M)); 	
	keySelector_->addItem("N", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_N)); 	
	keySelector_->addItem("O", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_O)); 	
	keySelector_->addItem("P", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_P)); 	
	keySelector_->addItem("Q", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_Q));
	keySelector_->addItem("R", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_R));
	keySelector_->addItem("S", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_S));
	keySelector_->addItem("T", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_T));
	keySelector_->addItem("U", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_U));
	keySelector_->addItem("V", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_V));
	keySelector_->addItem("W", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_W));
	keySelector_->addItem("X", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_X));
	keySelector_->addItem("Y", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_Y));
	keySelector_->addItem("Z", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_Z));

    mouseButtonSelector_ = new QComboBox();
    mouseButtonSelector_->addItem("Left", QVariant::fromValue<FakeInput::MouseButton>(FakeInput::Mouse_Left));
	mouseButtonSelector_->addItem("Middle", QVariant::fromValue<FakeInput::MouseButton>(FakeInput::Mouse_Middle));
	mouseButtonSelector_->addItem("Right", QVariant::fromValue<FakeInput::MouseButton>(FakeInput::Mouse_Right));

    QLabel* xLabel = new QLabel("dx: ");
    QLabel* yLabel = new QLabel("dy: ");
    mouseMotionX_ = new QSpinBox();
    mouseMotionX_->setSingleStep(50);
    mouseMotionX_->setMinimum(-10000);
    mouseMotionX_->setMaximum(10000);
    mouseMotionY_ = new QSpinBox();
    mouseMotionY_->setSingleStep(50);
    mouseMotionY_->setMinimum(-10000);
    mouseMotionY_->setMaximum(10000);

    mouseWheelDirection_ = new QComboBox();
    mouseWheelDirection_->addItem("Up");
	mouseWheelDirection_->addItem("Down");

    command_ = new QLineEdit();

    QLabel* timeLabel = new QLabel("miliseconds: ");
    waitTime_ = new QSpinBox();
    waitTime_->setSingleStep(50);
    waitTime_->setMaximum(10000);

    keyHBox->addWidget(keySelector_);
    mouseButtonHBox->addWidget(mouseButtonSelector_);
    mouseMotionHBox->addWidget(xLabel);
    mouseMotionHBox->addWidget(mouseMotionX_);
    mouseMotionHBox->addWidget(yLabel);
    mouseMotionHBox->addWidget(mouseMotionY_);
    mouseWheelHBox->addWidget(mouseWheelDirection_);
    commandHBox->addWidget(command_);
    waitHBox->addWidget(timeLabel);
    waitHBox->addWidget(waitTime_);

    keyOptions_->setLayout(keyHBox);
    mouseButtonOptions_->setLayout(mouseButtonHBox);
    mouseMotionOptions_->setLayout(mouseMotionHBox);
    mouseWheelOptions_->setLayout(mouseWheelHBox);
    commandOptions_->setLayout(commandHBox);
    waitOptions_->setLayout(waitHBox);

    QStackedWidget* stack = new QStackedWidget(this);
    stack->addWidget(keyOptions_);
    stack->addWidget(mouseButtonOptions_);
    stack->addWidget(mouseMotionOptions_);
    stack->addWidget(mouseWheelOptions_);
    stack->addWidget(commandOptions_);
    stack->addWidget(waitOptions_);

    vbox->addWidget(actionType_);
    vbox->addWidget(stack);
    vbox->addStretch(1);

    setLayout(vbox);

    connect(actionType_, SIGNAL(currentIndexChanged(int)), stack, SLOT(setCurrentIndex(int)));
}

QString ActionForm::addActionToSequence(FakeInput::ActionSequence& sequence)
{
    QString infoText = "";
    switch(actionType_->currentIndex())
    {
        case 0: {
            FakeInput::KeyType keyType = keySelector_->itemData(keySelector_->currentIndex()).value<FakeInput::KeyType>();
            FakeInput::Key key(keyType);
            sequence.press(key).release(key);

            infoText = actionType_->currentText();
            infoText.append(": ");
            infoText.append(key.name().c_str());
            break;
        }
        case 1: {
            FakeInput::MouseButton mouseButton =
                mouseButtonSelector_
                   ->itemData(mouseButtonSelector_->currentIndex())
                       .value<FakeInput::MouseButton>();
            sequence.press(mouseButton).release(mouseButton);

            infoText = actionType_->currentText();
            infoText.append(": ");
            infoText.append(mouseButtonSelector_->currentText());
            break;
        }
        case 2: {
            sequence.moveMouse(
                mouseMotionX_->text().toInt(),
                mouseMotionY_->text().toInt()
            );

            infoText = actionType_->currentText();
            infoText.append(": [ dx: ");
            infoText.append(mouseMotionX_->text());
            infoText.append(" ; dy: ");
            infoText.append(mouseMotionY_->text());
            infoText.append(" ]");
            break;
        }
        case 3: {
            infoText = actionType_->currentText();
            infoText.append(": ");

            if(mouseWheelDirection_->currentIndex() == 0)
            {
                sequence.wheelUp();
                infoText.append("Up");
            }
            else
            {
                sequence.wheelDown();
                infoText.append("Down");
            }

            break;
        }
        case 4: {
            sequence.runCommand(command_->text().toAscii().data());

            infoText = actionType_->currentText();
            infoText.append(": ");
            infoText.append(command_->text());
            break;
        }
        case 5: {
            sequence.wait(waitTime_->text().toInt());

            infoText = actionType_->currentText();
            infoText.append(": ");
            infoText.append(waitTime_->text());
            break;
        }
        default:
            break;
    }

    return infoText;
}

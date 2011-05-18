#ifndef TEST_GRABBER_HPP
#define TEST_GRABBER_HPP

#include <QWidget>

#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QComboBox>

#include "key.hpp"

class QLabel;
class QPushButton;

class Sender;

using FakeInput::Key;

class Grabber : public QWidget
{
    Q_OBJECT

    Q_ENUMS(FakeInput::KeyType);
public:
    Grabber();
    virtual ~Grabber();

#ifdef UNIX
    bool x11Event(XEvent* event);
#elif WIN32
    bool winEvent(MSG* message, long* result);
#endif

public slots:
    void grabKeyEvent();
    void keySelected(int index);

private:
#ifdef UNIX
    Display* display_;
    Window* window_;
#endif

    bool isReady_;
    bool isGrabbing_;

    QLabel* keyName_;

    QPushButton* grabButton_;
    QComboBox* keySelector_;

    QPushButton* sendButton_;

    Key key_;

    Sender* sender_;
};

#endif

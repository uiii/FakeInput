/**
 * This file is part of the FakeInput library (https://github.com/uiii/FakeInput)
 *
 * Copyright (C) 2011 by Richard Jedlicka <uiii.dev@gmail.com>
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "keyEventGrabber.hpp"

#include <iostream>

#include "keyEventSender.hpp"

using FakeInput::Key;

Q_DECLARE_METATYPE(FakeInput::KeyType);
Q_ENUMS(FakeInput::KeyType);

Grabber::Grabber():
    QWidget(0),
    isReady_(false),
    isGrabbing_(false)
{
    qRegisterMetaType<FakeInput::KeyType>("FakeInput::KeyType");

    QVBoxLayout *vbox = new QVBoxLayout(this);

    sender_ = new Sender();

    keyName_ = new QLabel("key name: <no key>", this);
    grabButton_ = new QPushButton("grab key event", this);
    grabButton_->setFocusPolicy(Qt::NoFocus);
    sendButton_ = new QPushButton("send key event", this);
    sendButton_->setFocusPolicy(Qt::NoFocus);

    keySelector_ = new QComboBox(this);
    keySelector_->setFocusPolicy(Qt::NoFocus);

    keySelector_->addItem("<no key>", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_NoKey));
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
	keySelector_->addItem("0", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_0));
	keySelector_->addItem("1", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_1));
	keySelector_->addItem("2", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_2));
	keySelector_->addItem("3", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_3));
	keySelector_->addItem("4", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_4));
	keySelector_->addItem("5", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_5));
	keySelector_->addItem("6", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_6));
	keySelector_->addItem("7", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_7));
	keySelector_->addItem("8", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_8));
	keySelector_->addItem("9", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_9));
	keySelector_->addItem("F1", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_F1)); 	
	keySelector_->addItem("F2", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_F2)); 	
	keySelector_->addItem("F3", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_F3)); 	
	keySelector_->addItem("F4", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_F4)); 	
	keySelector_->addItem("F5", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_F5)); 	
	keySelector_->addItem("F6", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_F6)); 	
	keySelector_->addItem("F7", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_F7)); 	
	keySelector_->addItem("F8", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_F8)); 	
	keySelector_->addItem("F9", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_F9)); 	
	keySelector_->addItem("F10", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_F10)); 	
	keySelector_->addItem("F11", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_F11)); 	
	keySelector_->addItem("F12", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_F12)); 	
	keySelector_->addItem("F13", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_F13)); 	
	keySelector_->addItem("F14", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_F14)); 	
	keySelector_->addItem("F15", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_F15)); 	
	keySelector_->addItem("F16", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_F16)); 	
	keySelector_->addItem("F17", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_F17)); 	
	keySelector_->addItem("F18", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_F18)); 	
	keySelector_->addItem("F19", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_F19)); 	
	keySelector_->addItem("F20", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_F20)); 	
	keySelector_->addItem("F21", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_F21)); 	
	keySelector_->addItem("F22", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_F22)); 	
	keySelector_->addItem("F23", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_F23)); 	
	keySelector_->addItem("F24", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_F24)); 	
	keySelector_->addItem("Escape", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_Escape)); 	
	keySelector_->addItem("Space", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_Space)); 	
	keySelector_->addItem("Return", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_Return)); 	
	keySelector_->addItem("Backspace", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_Backspace)); 	
	keySelector_->addItem("Tab", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_Tab)); 	
	keySelector_->addItem("Shift_L", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_Shift_L)); 	
	keySelector_->addItem("Shift_R", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_Shift_R)); 	
	keySelector_->addItem("Control_L", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_Control_L)); 	
	keySelector_->addItem("Control_R", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_Control_R)); 	
	keySelector_->addItem("Alt_L", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_Alt_L)); 	
	keySelector_->addItem("Alt_R", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_Alt_R)); 	
	keySelector_->addItem("Win_L", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_Win_L)); 	
	keySelector_->addItem("Win_R", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_Win_R)); 	
	keySelector_->addItem("Apps", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_Apps)); 	
	keySelector_->addItem("CapsLock", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_CapsLock)); 	
	keySelector_->addItem("NumLock", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_NumLock)); 	
	keySelector_->addItem("ScrollLock", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_ScrollLock)); 	
	keySelector_->addItem("PrintScreen", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_PrintScreen)); 	
	keySelector_->addItem("Pause", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_Pause)); 	
	keySelector_->addItem("Insert", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_Insert)); 	
	keySelector_->addItem("Delete", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_Delete)); 	
	keySelector_->addItem("PageUP", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_PageUP)); 	
	keySelector_->addItem("PageDown", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_PageDown)); 	
	keySelector_->addItem("Home", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_Home)); 	
	keySelector_->addItem("End", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_End)); 	
	keySelector_->addItem("Left", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_Left)); 	
	keySelector_->addItem("Right", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_Right)); 	
	keySelector_->addItem("Up", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_Up)); 	
	keySelector_->addItem("Down", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_Down)); 	
	keySelector_->addItem("Numpad0", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_Numpad0)); 	
	keySelector_->addItem("Numpad1", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_Numpad1)); 	
	keySelector_->addItem("Numpad2", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_Numpad2)); 	
	keySelector_->addItem("Numpad3", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_Numpad3)); 	
	keySelector_->addItem("Numpad4", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_Numpad4)); 	
	keySelector_->addItem("Numpad5", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_Numpad5)); 	
	keySelector_->addItem("Numpad6", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_Numpad6)); 	
	keySelector_->addItem("Numpad7", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_Numpad7)); 	
	keySelector_->addItem("Numpad8", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_Numpad8)); 	
	keySelector_->addItem("Numpad9", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_Numpad9)); 	
	keySelector_->addItem("NumpadAdd", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_NumpadAdd)); 	
	keySelector_->addItem("NumpadSubtract", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_NumpadSubtract)); 	
	keySelector_->addItem("NumpadMultiply", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_NumpadMultiply)); 	
	keySelector_->addItem("NumpadDivide", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_NumpadDivide)); 	
	keySelector_->addItem("NumpadDecimal", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_NumpadDecimal)); 	
	keySelector_->addItem("NumpadEnter", QVariant::fromValue<FakeInput::KeyType>(FakeInput::Key_NumpadEnter));

    QPushButton* closeButton = new QPushButton("close", this);

    vbox->addWidget(keyName_);
    vbox->addWidget(new QLabel("select:", this));
    vbox->addWidget(keySelector_);
    vbox->addWidget(new QLabel("or grab key:", this));
    vbox->addWidget(grabButton_);
    vbox->addWidget(sendButton_);
    vbox->addWidget(closeButton);

    setLayout(vbox);

    connect(grabButton_, SIGNAL(clicked()), this, SLOT(grabKeyEvent()));
    connect(grabButton_, SIGNAL(clicked()), this, SLOT(setFocus()));
    connect(keySelector_, SIGNAL(currentIndexChanged(int)), this, SLOT(keySelected(int)));
    connect(sendButton_, SIGNAL(pressed()), sender_, SLOT(show()));
    connect(closeButton, SIGNAL(pressed()), qApp, SLOT(quit()));

#ifdef UNIX
    display_ = XOpenDisplay(0);
#endif

    setLayout(vbox);
}

Grabber::~Grabber()
{
}

#ifdef UNIX
bool Grabber::x11Event(XEvent* event)
{
    if(isReady_ == false)
    {
        if(event->type == FocusIn)
        {
            display_ = event->xfocus.display;
            window_ = &(event->xfocus.window);
            
            isReady_ = true;
        }
    }

    if(isGrabbing_ == true)
    {
        if(event->type == KeyPress)// || event->type == KeyRelease)
        {
            key_ = FakeInput::Key(event);
            sender_->setKey(key_);

            keyName_->setText(QString("key name: ") + QString(key_.name().c_str()));

            XUngrabKeyboard(event->xkey.display, CurrentTime);
        }
        else if(event->type == KeyRelease && isGrabbing_)
        {
            isGrabbing_ = false;
        }
    }

    return false;
}
#elif WIN32
bool Grabber::winEvent(MSG* message, long* result)
{
    isReady_ = true;

    switch(message->message)
    {
        case WM_KEYUP:
        case WM_SYSKEYUP:
            if(isGrabbing_ == false) return false;
            key_ = FakeInput::Key(message);
            sender_->setKey(key_);

            keyName_->setText(QString("key name: ") + QString(key_.name().c_str()));

            isGrabbing_ = false;
        break;
        default:
        break;
    }

    return false;
}
#endif

void Grabber::keySelected(int index)
{
    FakeInput::KeyType type = keySelector_->itemData(index).value<FakeInput::KeyType>();

    key_ = Key(type);
    sender_->setKey(key_);
    keyName_->setText(QString("key name: ") + QString(key_.name().c_str()));
    isGrabbing_ = false;
}

void Grabber::grabKeyEvent()
{
    keySelector_->setCurrentIndex(0);

    if(isReady_ == true)
    {
#ifdef UNIX
        XGrabKeyboard(display_, *window_, false, GrabModeAsync, GrabModeAsync, CurrentTime);
#endif
        isGrabbing_ = true;
    }
    else
    {
        std::cerr << "Canot grab keyboard" << std::endl;
    }
}

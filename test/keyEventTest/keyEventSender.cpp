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

#include "keyEventSender.hpp"

#include <QVBoxLayout>
#include <QPushButton>
#include <iostream>

#include "keyboard.hpp"

Sender::Sender():
    QWidget(0, Qt::WindowStaysOnTopHint
#ifdef UNIX
            | Qt::X11BypassWindowManagerHint
#endif
    )
{
    setFocusPolicy(Qt::NoFocus);
    QVBoxLayout* vbox = new QVBoxLayout(this);
    QPushButton* sendButton = new QPushButton("send key event", this);
    QPushButton* quitButton = new QPushButton("close", this);
    vbox->addWidget(sendButton);
    vbox->addWidget(quitButton);

    setLayout(vbox);

    connect(sendButton, SIGNAL(pressed()), this, SLOT(sendPress()));
    connect(sendButton, SIGNAL(released()), this, SLOT(sendRelease()));
    connect(quitButton, SIGNAL(pressed()), this, SLOT(hide()));

#ifdef UNIX
    display_ = XOpenDisplay(0);
#endif
}

Sender::~Sender() {}

#ifdef WINDOWS
bool Sender::winEvent(MSG* message, long* result)
{
    if(message->message == WM_ACTIVATE)
    {
        focusWindow_ = (HWND)message->lParam;
    }

    return false;
}
#endif

void Sender::setKey(FakeInput::Key key)
{
    key_ = key;
}

void Sender::sendPress()
{
#ifdef WINDOWS
    SetActiveWindow(focusWindow_);
#endif
    FakeInput::Keyboard::pressKey(key_);
}

void Sender::sendRelease()
{
#ifdef WINDOWS
    SetActiveWindow(focusWindow_);
#endif
    FakeInput::Keyboard::releaseKey(key_);
}

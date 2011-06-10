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

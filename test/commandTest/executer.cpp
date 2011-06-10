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

#include "executer.hpp"

#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>

#include <string>
#include <iostream>

#include "system.hpp"

Executer::Executer():
    QWidget(0)
{
    QHBoxLayout* hbox = new QHBoxLayout();

    cmd_ = new QLineEdit(this);
    cmd_->setFixedWidth(300);

    QPushButton* runButton = new QPushButton("Run", this);

    hbox->addWidget(cmd_);
    hbox->addWidget(runButton);

    setLayout(hbox);
    
    connect(runButton, SIGNAL(clicked()), this, SLOT(runCommand()));
}

Executer::~Executer()
{
}

void Executer::runCommand()
{ 
    FakeInput::System::run(cmd_->text().toAscii().data());
}

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

#include "actionsController.hpp"

#include <QPushButton>
#include <QSizePolicy>
#include <QLabel>

#include <iostream>

ActionsController::ActionsController():
    QDialog(0)
{
    QHBoxLayout* hbox = new QHBoxLayout(this);

    QWidget* action = new QWidget();
    actionVBox_ = new QVBoxLayout();
    actionVBox_->addWidget(new QLabel("Actions' list: "));
    actionVBox_->addStretch();
    action->setLayout(actionVBox_);

    form_ = new ActionForm(this);

    QPushButton* addButton = new QPushButton("Add action", this);
    addButton->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);

    QPushButton* sendButton = new QPushButton("Send", this);
    sendButton->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);

    hbox->addWidget(action);
    hbox->addWidget(form_);
    hbox->addWidget(addButton);
    hbox->addWidget(sendButton);

    connect(addButton, SIGNAL(clicked()), this, SLOT(addAction()));
    connect(sendButton, SIGNAL(clicked()), this, SLOT(sendActionSequence()));

    setLayout(hbox);
}

void ActionsController::addAction()
{
    QString infoText = form_->addActionToSequence(actionSequence_);

    //QWidget* info = new QWidget(this);

    //QVBoxLayout* infoVBox = new QVBoxLayout(this);
    //infoVBox->addWidget(new QLabel(infoText, this));

    //info->setLayout(infoVBox);

    actionVBox_->insertWidget(actionVBox_->count() - 1, new QLabel(infoText, this));
}

void ActionsController::sendActionSequence()
{
    actionSequence_.send();
}

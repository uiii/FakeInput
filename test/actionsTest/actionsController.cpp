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

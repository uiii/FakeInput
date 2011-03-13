#include "executer.h"

#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>

#include <string>
#include <iostream>

#include "command.h"

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
    wc::Command::run(cmd_->text().toAscii().data());
}

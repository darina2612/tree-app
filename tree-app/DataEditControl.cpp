#include "DataEditControl.h"

#include <QLabel>
#include <QLineEdit>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QPushButton>

#include <iostream>

DataEditControl::DataEditControl()
{
    setup();
}

DataEditControl::~DataEditControl()
{
    delete box_;
}

void DataEditControl::setup()
{
    box_ = new QGroupBox;
    layout_ = new QVBoxLayout;

    nameLabel_ = new QLabel;
    nameLabel_->setText("Име : ");

    nameEdit_ = new QLineEdit;
    layout_->addWidget(nameLabel_);
    layout_->addWidget(nameEdit_);

    okButton_ = new QPushButton("OK");
    QObject::connect(okButton_, &QPushButton::pressed,
    [this]()
    {
        auto newName = nameEdit_->text().toLocal8Bit().data();
        dataPtr_->setName(newName);
        box_->hide();
    });
    layout_->addWidget(okButton_);

    box_->setLayout(layout_);
}

void DataEditControl::updateData(const PersonDataPtr& data)
{
    dataPtr_ = data;
    nameEdit_->setText(dataPtr_->getName().c_str());
}

void DataEditControl::show() const
{
    if(box_ != nullptr)
        box_->show();
}

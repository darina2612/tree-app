#include "DataEditControl.h"

#include <QLabel>
#include <QLineEdit>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QPushButton>
#include "PictureChooser.h"
#include "TextLineEditControl.h"

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
    auto layout = new QVBoxLayout;

    nameEdit_ = new TextLineEditControl("Име : ");
    layout->addWidget(nameEdit_);

    pictureChooser_ = new PictureChooser();
    layout->addWidget(pictureChooser_);

    auto okButton = new QPushButton("OK");
    QObject::connect(okButton, &QPushButton::pressed,
    [this]()
    {
        auto newName = nameEdit_->text().toLocal8Bit().data();
        dataPtr_->setName(newName);
        dataPtr_->setPictureFileName(pictureChooser_->fileName().toLocal8Bit().data());
        if(okClickedCalback_)
            okClickedCalback_(dataPtr_);
        box_->hide();
    });
    layout->addWidget(okButton);

    box_->setLayout(layout);
}

void DataEditControl::updateData(const PersonDataPtr& data,
                                 const std::function<void(const PersonDataPtr&)>& okCalback)
{
    dataPtr_ = data;
    nameEdit_->setText(dataPtr_->getName().c_str());
    pictureChooser_->setFileName(dataPtr_->getPictureFileName().c_str());
    okClickedCalback_ = okCalback;
}

void DataEditControl::show() const
{
    if(box_ != nullptr)
        box_->show();
}

#include "TextLineEditControl.h"

#include <QLabel>
#include <cassert>
#include <QLineEdit>
#include <QHBoxLayout>

TextLineEditControl::TextLineEditControl(const QString& labelText,
                                         QWidget *parent) : QWidget(parent)
{
    auto layout = new QHBoxLayout(this);
    layout->setMargin(0);

    lineEdit_ = new QLineEdit(this);
    layout->addWidget(lineEdit_);

    label_ = new QLabel;
    label_->setText(labelText);

    layout->addWidget(label_);
    layout->addWidget(lineEdit_);
}

QString TextLineEditControl::text() const
{
    assert(lineEdit_ != nullptr);

    return lineEdit_->text();
}

void TextLineEditControl::setText(const QString& text)
{
    assert(lineEdit_ != nullptr);

    return lineEdit_->setText(text);
}

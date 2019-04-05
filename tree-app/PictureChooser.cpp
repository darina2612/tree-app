#include "PictureChooser.h"

#include <QLineEdit>
#include <QHBoxLayout>
#include <QPushButton>
#include <QFileDialog>

PictureChooser::PictureChooser(QWidget *parent) :
    QWidget(parent)
{
    auto layout = new QHBoxLayout(this);
    layout->setMargin(0);

    lineEdit_ = new QLineEdit(this);
    layout->addWidget(lineEdit_);

    connect(lineEdit_, SIGNAL(textChanged(const QString&)),
            this, SIGNAL(fileNameChanged(const QString&)));

    button_ = new QPushButton( "...", this);
    button_->setFixedWidth( button_->fontMetrics().width(" ... " ));
    layout->addWidget(button_);

    connect(button_, SIGNAL(clicked()), this, SLOT(chooseFile()));

    setFocusProxy(lineEdit_);
}

void PictureChooser::setFileName(const QString& fileName)
{
    lineEdit_->setText(fileName);
}

QString PictureChooser::fileName() const
{
    return lineEdit_->text();
}

void PictureChooser::chooseFile()
{
    QString fileName;
    fileName = QFileDialog::getOpenFileName(this, lineEdit_->text());

    if(!fileName.isEmpty())
    {
        lineEdit_->setText(fileName);
        emit fileNameChanged(fileName);
    }
}

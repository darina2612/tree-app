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

    auto buttonText = " Отвори ";
    button_ = new QPushButton(buttonText, this);
    button_->setFixedWidth(button_->fontMetrics().width(buttonText));
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

    //Source : https://stackoverflow.com/questions/1604440/how-to-set-selected-filter-on-qfiledialog
    QString selfilter = tr("JPEG (*.jpg *.jpeg)");
    fileName = QFileDialog::getOpenFileName(this, "Избор на картинка",
                                            "", tr("All files (*.*);;JPEG (*.jpg *.jpeg);;TIFF (*.tif)" ),
                                            &selfilter);

    if(!fileName.isEmpty())
    {
        lineEdit_->setText(fileName);
        emit fileNameChanged(fileName);
    }
}

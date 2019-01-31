#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::paintEvent(QPaintEvent* )
{
    QPainter painter(this);

    QRect r(100, 100, 200, 100);

    painter.fillRect(r, QGradient::LinearGradient);
}

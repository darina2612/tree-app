#include "dialog.h"
#include "ui_dialog.h"
#include "Drawer.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    tree_ = std::make_shared<FamilyTree>();
    //tree_->addValue(std::make_shared<FamilyNode>(nullptr, {100, 100, 50, 50}));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::paintEvent(QPaintEvent* )
{
    QPainter painter(this);
    Drawer drawer(&painter);

    tree_->draw(drawer);
}

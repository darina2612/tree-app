#include "dialog.h"
#include "ui_dialog.h"
#include "Drawer.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    //testing, should be removed
    auto personData = std::make_shared<PersonData>();
    Rect frame{0, 0, 50, 50};
    FamilyNode node{personData, frame};

    tree_ = std::make_shared<FamilyTree>(node);

    auto root = tree_->getRoot();

    for(size_t i = 0; i < 3; ++i)
        root->addChild(node);
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

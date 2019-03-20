#include "dialog.h"

#include <cassert>
#include "Drawer.h"
#include "ui_dialog.h"
#include "ConversionUtils.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    //testing, should be removed
    auto personData = std::make_shared<PersonData>("Text", "../tree-app/tree-app/test_img.jpg");
    Rect frame{0, 0, 200, 200};
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
    if(tree_ == nullptr)
        return;

    QPainter painter(this);
    Drawer drawer(&painter);

    tree_->draw(drawer);
}

void Dialog::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(tree_ == nullptr)
        return;

    if(event == nullptr)
    {
        assert(false);
        return;
    }

    Point pos{event->x(), event->y()};

    auto node = tree_->getDataForNodeAtPosition(pos);

    if(node != nullptr)
    {
        //do something
        this->repaint();
    }
}

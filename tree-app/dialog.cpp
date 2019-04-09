#include "dialog.h"

#include <QMenu>
#include <cassert>
#include "Drawer.h"
#include "ui_dialog.h"
#include "ConversionUtils.h"
#include "DataEditControl.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    this->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(this, SIGNAL(customContextMenuRequested(const QPoint&)),
            this, SLOT(showContextMenu(const QPoint&)));

    //testing, should be removed
    auto personData = std::make_shared<PersonData>("Text", "../tree-app/tree-app/test_img.jpg");
    Rect frame{0, 0, 200, 200};
    FamilyNode node{personData, frame};

    tree_ = std::make_shared<FamilyTree>(node);

    auto root = tree_->getRoot();

    for(size_t i = 0; i < 3; ++i)
        root->addChild(node.copy());
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

void Dialog::mouseDoubleClickEvent(QMouseEvent* event)
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
        nodeEditControl_.updateData(node);
        nodeEditControl_.show();
        //this->repaint();
    }
}

void Dialog::showContextMenu(const QPoint& pos)
{
   auto node = tree_->getNodeAtPosition(ConversionUtils::pointFromQPoint(pos));

   if(node == nullptr)
       return;

   QMenu contextMenu(tr("Меню"), this);
   QAction addChildAction("Добaви дете", this);
   QObject::connect(&addChildAction, &QAction::triggered,
   [this, node]()
   {
       PersonDataPtr newChild = std::make_shared<PersonData>();
       nodeEditControl_.updateData(newChild, [node](const PersonDataPtr& data)
       {
           node->addChild({data, {0, 0, 200, 200}});
       });
       nodeEditControl_.show();
   });
   contextMenu.addAction(&addChildAction);

   contextMenu.exec(mapToGlobal(pos));
}

#include "dialog.h"

#include <QMenu>
#include <cassert>
#include <QMenuBar>
#include "Drawer.h"
#include <QVBoxLayout>
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

    auto mainLayout = new QVBoxLayout(this);
    auto menuBar = new QMenuBar();
    mainLayout->addWidget(menuBar);
    menuBar->addAction("File");

    //testing, should be removed
    auto personData = std::make_shared<PersonData>("Text", ROOT_DIR "/test_img.jpg");
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
    }
}

void Dialog::showEvent(QShowEvent* event)
{
    if(event != nullptr && !event->spontaneous())
        updateSize();
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
       nodeEditControl_.updateData(newChild, [this, node](const PersonDataPtr& data)
       {
           node->addChild({data, {0, 0, 200, 200}});
           updateSize();
       });
       nodeEditControl_.show();
   });
   contextMenu.addAction(&addChildAction);

   QAction  deleteAction("Изтрий", this);
   QObject::connect(&deleteAction, &QAction::triggered,
   [this, &pos]()
   {
       tree_->removeSubtreeAtPosition(ConversionUtils::pointFromQPoint(pos));
       repaint();
   });
   contextMenu.addAction(&deleteAction);

   contextMenu.exec(mapToGlobal(pos));
}

void Dialog::showFileMenu()
{
    QMenu fileMenu(tr("Файл"), this);
    QAction openFileAction("Отвори", this);
    QObject::connect(&openFileAction, &QAction::triggered,
    []()
    {
//        PersonDataPtr newChild = std::make_shared<PersonData>();
//        nodeEditControl_.updateData(newChild, [this, node](const PersonDataPtr& data)
//        {
//            node->addChild({data, {0, 0, 200, 200}});
//            updateSize();
//        });
//        nodeEditControl_.show();
    });
    fileMenu.addAction(&openFileAction);

    fileMenu.exec();
}

void Dialog::updateSize()
{
    if(tree_ == nullptr)
        return;

    auto treeBb = tree_->getExtendedBoundingBox();
    auto size = sizeHint();

    size.setWidth(std::max(size.width(), treeBb.width()));
    size.setHeight(std::max(size.height(), treeBb.height()));

    resize(size);
}

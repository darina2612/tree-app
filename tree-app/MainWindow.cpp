#include "MainWindow.h"

#include <QMenu>
#include <cassert>
#include <QMenuBar>
#include "Drawer.h"
#include <QFileDialog>
#include <QVBoxLayout>
#include "DeleteCommand.h"
#include "EditController.h"
#include "ConversionUtils.h"
#include "DataEditControl.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    this->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(this, SIGNAL(customContextMenuRequested(const QPoint&)),
            this, SLOT(showContextMenu(const QPoint&)));

    createActions();
    createMenus();

    //testing, should be removed
    auto personData = std::make_shared<PersonData>("Text", ROOT_DIR "/test_img.jpg");
    Rect frame{0, 0, 200, 200};
    FamilyNode node{personData, frame};

    tree_ = std::make_shared<FamilyTree>(node);

    auto root = tree_->getRoot();

    for(size_t i = 0; i < 3; ++i)
        root->addChild(node.copy());
}

void MainWindow::paintEvent(QPaintEvent* )
{
    if(tree_ == nullptr)
        return;

    QPainter painter(this);
    Drawer drawer(&painter);

    tree_->draw(drawer);
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent* event)
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

void MainWindow::showEvent(QShowEvent* event)
{
    if(event != nullptr && !event->spontaneous())
        updateSize();
}

void MainWindow::createActions()
{
    //File

    open = new QAction(tr("&Open"), this);
    open->setStatusTip(tr("Open existing file."));
    connect(open, &QAction::triggered, this, &MainWindow::openFile);

    save = new QAction(tr("&Save"), this);
    save->setStatusTip(tr("Save current file."));
    save->setShortcut(QKeySequence::Save);
    connect(save, &QAction::triggered, this, &MainWindow::saveFile);

    //Edit

    undoAction = new QAction(tr("&Undo"), this);
    undoAction->setStatusTip(tr("Undo last change."));
    undoAction->setShortcut(QKeySequence::Undo);
    connect(undoAction, &QAction::triggered, this, &MainWindow::undo);

    redoAction = new QAction(tr("&Redo"), this);
    redoAction->setStatusTip(tr("Redo last change."));
    redoAction->setShortcut(QKeySequence::Redo);
    connect(redoAction, &QAction::triggered, this, &MainWindow::redo);
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(open);
    fileMenu->addAction(save);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(undoAction);
    editMenu->addAction(redoAction);
}

void MainWindow::showContextMenu(const QPoint& pos)
{
   auto node = tree_->getNodeAtPosition(ConversionUtils::pointFromQPoint(pos));

   if(node == nullptr)
       return;

   QMenu contextMenu(tr("Menu"), this);
   QAction addChildAction("Add child", this);
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

   QAction  deleteAction("Delete", this);
   QObject::connect(&deleteAction, &QAction::triggered,
   [this, &pos]()
   {
       auto deleteCommand = std::make_shared<DeleteCommand>(tree_,
                                                            tree_->getNodePositionInfo(ConversionUtils::pointFromQPoint(pos)));
       editor_.addCommand(deleteCommand);
       repaint();
   });
   contextMenu.addAction(&deleteAction);

   contextMenu.exec(mapToGlobal(pos));
}

void MainWindow::updateSize()
{
    if(tree_ == nullptr)
        return;

    auto treeBb = tree_->getExtendedBoundingBox();
    auto size = sizeHint();

    size.setWidth(std::max(size.width(), treeBb.width()));
    size.setHeight(std::max(size.height(), treeBb.height()));

    resize(size);
}

void MainWindow::openFile()
{
    QFileDialog* fileDialog = new QFileDialog(this);

    QString filename = QFileDialog::getOpenFileName(fileDialog,"Open tree", "", "Tree (*.tree)");

    if(filename.size() == 0)
    {
        return;
    }

    tree_ = std::make_shared<FamilyTree>(filename.toLocal8Bit().data());
}

void MainWindow::saveFile()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Save File"), "",
                               "Tree (*.tree)");

    tree_->save(filename.toLocal8Bit().data());
}

void MainWindow::undo()
{
    editor_.undo();

    repaint();
}

void MainWindow::redo()
{
    editor_.redo();

    repaint();
}

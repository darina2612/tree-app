#ifndef DIALOG_H
#define DIALOG_H

#include <QMainWindow>

#include <QtGui>
#include <QtCore>
#include "FamilyTree.h"
#include "EditController.h"
#include "DataEditControl.h"

namespace Ui {
class Dialog;
}

class QMenu;
class QAction;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override = default;

protected:
    void paintEvent(QPaintEvent*) override;

    void mouseDoubleClickEvent(QMouseEvent* event) override;

    void showEvent(QShowEvent* event) override;

private slots:
    void createActions();
    void createMenus();

    void showContextMenu(const QPoint& pos);

private:

    void updateSize();

    void openFile();
    void saveFile();

    FamilyTreePtr tree_;
    EditController editor_;

    DataEditControl nodeEditControl_;

    //Menus
    QMenu* fileMenu;

    //Actions
    QAction* open;
    QAction* save;
};

#endif // DIALOG_H

#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

#include <QtGui>
#include <QtCore>
#include "FamilyTree.h"
#include "DataEditControl.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog() override;

private:
    Ui::Dialog *ui;

protected:
    void paintEvent(QPaintEvent*) override;

    void mouseDoubleClickEvent(QMouseEvent* event) override;

    void showEvent(QShowEvent* event) override;

private slots:
    void showContextMenu(const QPoint& pos);

    void showFileMenu();

private:

    void updateSize();

    FamilyTreePtr tree_;

    DataEditControl nodeEditControl_;
};

#endif // DIALOG_H

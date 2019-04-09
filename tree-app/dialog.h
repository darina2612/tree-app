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
    void paintEvent(QPaintEvent* e) override;

    void mouseDoubleClickEvent(QMouseEvent* event) override;

private slots:
    void showContextMenu(const QPoint& pos);

private:
    FamilyTreePtr tree_;

    DataEditControl nodeEditControl_;
};

#endif // DIALOG_H

#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

#include <QtGui>
#include <QtCore>
#include "FamilyTree.h"

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

    FamilyTreePtr tree_;
};

#endif // DIALOG_H

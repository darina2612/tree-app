#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

#include <QtGui>
#include <QtCore>

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
};

#endif // DIALOG_H

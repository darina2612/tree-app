#pragma once
#include <QWidget>

// Source : https://doc.qt.io/archives/3.3/designer-manual-7.html

class QLineEdit;
class QPushButton;

class PictureChooser : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(QString fileName READ fileName WRITE setFileName)

public:
    explicit PictureChooser(QWidget *parent = nullptr);

    QString fileName() const;

public slots:
    void setFileName(const QString& fileName);

signals:
    void fileNameChanged(const QString& fileName);

private slots:
    void chooseFile();

private:
    QLineEdit* lineEdit_;
    QPushButton* button_;
};

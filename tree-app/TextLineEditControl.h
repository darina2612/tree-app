#pragma once

#include <memory>
#include <QWidget>
#include <functional>

class QLabel;
class QLineEdit;

class TextLineEditControl : public QWidget
{
    Q_OBJECT
public:
    explicit TextLineEditControl(const QString& labelText,
                                 QWidget *parent = nullptr);

    QString text() const;
    void setText(const QString& text);

signals:

public slots:

private:
    QLabel* label_;
    QLineEdit* lineEdit_;
};

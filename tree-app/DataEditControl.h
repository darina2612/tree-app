#pragma once

#include "PersonData.h"

class QGroupBox;
class QVBoxLayout;
class QLineEdit;
class QLabel;
class QPushButton;

class DataEditControl
{
public:
    DataEditControl();
    ~DataEditControl();

    void updateData(const PersonDataPtr& data);

    void show() const;

protected:

    void setup();

    PersonDataPtr dataPtr_;

    QGroupBox* box_;
    QVBoxLayout* layout_;
    QLabel* nameLabel_;
    QLineEdit* nameEdit_;
    QPushButton* okButton_;
};

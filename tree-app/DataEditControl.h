#pragma once

#include "PersonData.h"


class QGroupBox;
class TextLineEditControl;
class PictureChooser;

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
    TextLineEditControl* nameEdit_;
    PictureChooser* pictureChooser_;
};

#pragma once

#include <functional>
#include "PersonData.h"

class QGroupBox;
class TextLineEditControl;
class PictureChooser;

class DataEditControl
{
public:
    DataEditControl();
    ~DataEditControl();

    void updateData(const PersonDataPtr& data,
                    const std::function<void(const PersonDataPtr&)>& okCalback =
                    std::function<void(const PersonDataPtr&)>());

    void show() const;

protected:

    void setup();

    PersonDataPtr dataPtr_;

    QGroupBox* box_;
    TextLineEditControl* nameEdit_;
    PictureChooser* pictureChooser_;

    std::function<void(const PersonDataPtr&)> okClickedCalback_;
};

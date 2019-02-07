#pragma once

#include "Rect.h"
#include "Drawer.h"
#include "PersonData.h"

class FamilyNode
{
public:
    FamilyNode() = default;

    void draw(Drawer& drawer);

protected:
    PersonDataPtr data_;
    Rect frame_;
};

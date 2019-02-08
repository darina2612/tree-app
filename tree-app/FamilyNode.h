#pragma once

#include "Rect.h"
#include "Drawer.h"
#include "PersonData.h"

class FamilyNode
{
public:
    FamilyNode() = default;

    FamilyNode(const PersonDataPtr& data, const Rect& frame);

    void draw(Drawer& drawer);

protected:
    PersonDataPtr data_;
    Rect frame_;
};

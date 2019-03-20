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

    Rect& getFrame();
    const Rect& getFrame() const;

    PersonDataPtr getPersonData();

protected:
    PersonDataPtr data_;
    Rect frame_;
};

using FamilyNodePtr = std::shared_ptr<FamilyNode>;

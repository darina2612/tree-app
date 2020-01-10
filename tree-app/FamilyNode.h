#pragma once

#include "Rect.h"
#include "Drawer.h"
#include <iostream>
#include "PersonData.h"

class FamilyNode
{
public:
    FamilyNode() = default;

    FamilyNode(PersonDataPtr data, const Rect& frame);

    //deep copy
    FamilyNode copy() const;

    void draw(Drawer& drawer);

    Rect& getFrame();
    const Rect& getFrame() const;

    PersonDataPtr getPersonData();

    void serialize(std::ostream& os) const;
    void deserialize(std::istream& is);

protected:
    PersonDataPtr data_;
    Rect frame_;
};

using FamilyNodePtr = std::shared_ptr<FamilyNode>;

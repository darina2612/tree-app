#pragma once

#include "Tree.h"
#include "PersonData.h"

class Drawer;

class FamilyTree : Tree<PersonData>
{
public:
    void draw(Drawer& drawer);
};

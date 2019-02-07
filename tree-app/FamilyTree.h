#pragma once

#include "Tree.h"
#include "FamilyNode.h"

class Drawer;

class FamilyTree : Tree<FamilyNode>
{
public:
    void draw(Drawer& drawer);

protected:
    void draw(const NodePtr& root, Drawer& drawer);
};

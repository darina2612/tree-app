#pragma once

#include "Tree.h"
#include "FamilyNode.h"

class Drawer;

class FamilyTree : public Tree<FamilyNode>
{
public:
    void draw(Drawer& drawer);

protected:
    void draw(const NodePtr& root, Drawer& drawer);
};

using FamilyTreePtr = std::shared_ptr<FamilyTree>;

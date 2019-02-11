#pragma once

#include <map>
#include "Tree.h"
#include "FamilyNode.h"

class Drawer;

class FamilyTree : public Tree<FamilyNode>
{
public:
    FamilyTree();

    FamilyTree(const FamilyNode& rootVal);

    FamilyTree(const FamilyTree& other) = delete;

    void draw(Drawer& drawer);

protected:
    void draw(const NodePtr& root, Drawer& drawer);

    void updateLayout();

    void updateLevelLayout(NodesList& levelNodes, int horizontalOffset, int& verticalOffset);

    void updateLevelsWidths();

    int maxLevelWidth() const;

    int levelsVerticalOffset_;
    int nodesHorizontalOffset_;

    std::map<size_t, int> levelsWidths_;
};

using FamilyTreePtr = std::shared_ptr<FamilyTree>;

#pragma once

#include <map>
#include "Tree.h"
#include "FamilyNode.h"

class Drawer;
struct Point;

class FamilyTree : public Tree<FamilyNode>
{
public:
    FamilyTree();

    FamilyTree(const FamilyNode& rootVal);

    FamilyTree(const FamilyTree& other) = delete;

    void draw(Drawer& drawer);

    PersonDataPtr getDataForNodeAtPosition(const Point& pos) const;

protected:
    void draw(const NodePtr& root, Drawer& drawer);

    PersonDataPtr getDataForNodeAtPosition(const NodePtr& root,  const Point& pos) const;

    void drawLinkLines(const NodePtr& root, Drawer& drawer) const;

    void updateLayout();

    void updateLevelLayout(NodesList& levelNodes, int horizontalOffset, int& verticalOffset);

    void updateLevelsWidths();

    int maxLevelWidth() const;

    int levelsVerticalOffset_;
    int nodesHorizontalOffset_;

    std::map<size_t, int> levelsWidths_;
};

using FamilyTreePtr = std::shared_ptr<FamilyTree>;

#pragma once

#include <map>
#include "Tree.h"
#include "Rect.h"
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

    NodePtr getNodeAtPosition(const Point& pos) const;

    PersonDataPtr getDataForNodeAtPosition(const Point& pos) const;

    void removeSubtreeAtPosition(const Point& pos);

    Rect getBoundingBox() const;

    Rect getExtendedBoundingBox() const;

    void nodeChanged() override;

    void serialize(std::ostream& os) const override;
    void deserialize(std::istream& is) override;

protected:
    void draw(const NodePtr& root, Drawer& drawer);

    NodePtr getNodeAtPosition(const NodePtr& root, const Point& pos) const;

    bool removeSubtreeAtPosition(NodePtr& root, const Point& pos);

    Rect getBoundingBox(const NodePtr& root) const;

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

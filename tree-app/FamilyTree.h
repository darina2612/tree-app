#pragma once

#include <map>
#include "Tree.h"
#include "Rect.h"
#include "FamilyNode.h"
#include "PositionInfo.h"

class Drawer;
struct Point;

using FamilyTreeIdType = int;

class FamilyTree : public Tree<FamilyNode, FamilyTreeIdType>
{
public:
    FamilyTree();

    FamilyTree(const FamilyNode& rootVal);

    FamilyTree(const std::string& filename);

    FamilyTree(const FamilyTree& other) = delete;

    void draw(Drawer& drawer);

    NodePtr getNodeAtPosition(const Point& pos) const;

    PersonDataPtr getDataForNodeAtPosition(const Point& pos) const;

    void removeSubtree(const PositionInfo<FamilyTreeIdType>& posInfo);

    void addSubtree(NodePtr& subtreeRoot, const PositionInfo<FamilyTreeIdType>& posInfo);

    Rect getBoundingBox() const;

    Rect getExtendedBoundingBox() const;

    void nodeChanged() override;

    void save(const std::string& filename) const;

    void serialize(std::ostream& os) const override;
    void deserialize(std::istream& is) override;

    FamilyTreeIdType getNextId() override;

    PositionInfo<FamilyTreeIdType> getNodePositionInfo(const Point& pos) const;

protected:
    void draw(const NodePtr& root, Drawer& drawer);

    NodePtr getNodeAtPosition(const NodePtr& root, const Point& pos) const;

    NodePtr getParent(size_t id) const;

    NodePtr getParent(const NodePtr& root, size_t id) const;

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

    FamilyTreeIdType maxNodeId_{};
};

using FamilyTreePtr = std::shared_ptr<FamilyTree>;

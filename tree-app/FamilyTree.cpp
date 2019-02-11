#include "FamilyTree.h"

#include <cassert>
#include <algorithm>

FamilyTree::FamilyTree() : Tree<FamilyNode>()
{
    levelsVerticalOffset_ = 30;
    nodesHorizontalOffset_ = 20;
}

FamilyTree::FamilyTree(const FamilyNode& rootVal) :  Tree<FamilyNode>(rootVal)
{
    levelsVerticalOffset_ = 30;
    nodesHorizontalOffset_ = 20;
}

void FamilyTree::draw(Drawer& drawer)
{
    draw(root_, drawer);
}

// Helpers
void FamilyTree::draw(const NodePtr& root, Drawer& drawer)
{
    if(root == nullptr)
        return;

    updateLayout();

    root->getValue().draw(drawer);

    root->doWithChildren([this, &drawer](const auto& child)
    {
        draw(child, drawer);
    });
}

void FamilyTree::updateLayout()
{
    updateLevelsWidths();

    size_t levelsCount = height();

    int maxWidth = maxLevelWidth();

    int currentVerticalOffset = 0;

    for(size_t i = 0; i < levelsCount; ++i)
    {
        NodesList levelNodes;
        getNodesAtLevel(levelNodes, i);

        int horizontalLevelOffset = (maxWidth - levelsWidths_[i]) / 2;

        updateLevelLayout(levelNodes, horizontalLevelOffset,  currentVerticalOffset);
    }
}

void FamilyTree::updateLevelLayout(NodesList& levelNodes, int horizontalOffset, int& verticalOffset)
{
    int verticalOffsetUpdate = 0;

    verticalOffset += levelsVerticalOffset_;

    for(auto& node : levelNodes)
    {
        Rect& frame = node->getValue().getFrame();
        verticalOffsetUpdate = std::max(verticalOffsetUpdate, frame.height());

        horizontalOffset += nodesHorizontalOffset_;
        frame.origin_ = {horizontalOffset, verticalOffset};
        horizontalOffset += frame.width();
    }


    verticalOffset += verticalOffsetUpdate;
}

void FamilyTree::updateLevelsWidths()
{
    size_t levelsCount = height();

    for(size_t i = 0; i < levelsCount; ++i)
    {
        NodesList levelNodes;
        getNodesAtLevel(levelNodes, i);

        levelsWidths_[i] = 0;

        for(const auto& node : levelNodes)
            levelsWidths_[i] += node->getValue().getFrame().width();

        levelsWidths_[i] += static_cast<int>(levelNodes.size() + 1) * nodesHorizontalOffset_;
    }
}

int FamilyTree::maxLevelWidth() const
{
    auto max = std::max_element(levelsWidths_.begin(), levelsWidths_.end(),
                                [](const auto& left, const auto& right)
    {
        return left.second < right.second;
    });

    if(max == levelsWidths_.end())
    {
        assert(false);
        return  0;
    }

    return max->second;
}

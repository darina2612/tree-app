#include "FamilyTree.h"

#include <cassert>
#include <fstream>
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

FamilyTree::FamilyTree(const std::string& filename)
{
    std::ifstream file{};
    file.open(filename, std::ios::in | std::ios::binary);

    if(!file)
    {
        //TODO : Error output
        return;
    }

    deserialize(file);
}

void FamilyTree::draw(Drawer& drawer)
{
    draw(root_, drawer);
}

FamilyTree::NodePtr FamilyTree::getNodeAtPosition(const Point& pos) const
{
    return getNodeAtPosition(root_, pos);
}

PersonDataPtr FamilyTree::getDataForNodeAtPosition(const Point& pos) const
{
    auto node = getNodeAtPosition(pos);

    if(node != nullptr)
        return node->getValue().getPersonData();

    return nullptr;
}

void FamilyTree::removeSubtreeAtPosition(const Point& pos)
{
    if(root_ != nullptr && root_->getValue().getFrame().contains(pos))
        root_.reset();

    removeSubtreeAtPosition(root_, pos);
}

Rect FamilyTree::getBoundingBox() const
{
    return getBoundingBox(root_);
}

Rect FamilyTree::getExtendedBoundingBox() const
{
    auto bb = getBoundingBox();
    bb.extendWith({nodesHorizontalOffset_ * 2, levelsVerticalOffset_ * 2});

    return bb;
}

void FamilyTree::nodeChanged()
{
    updateLayout();
}

void FamilyTree::serialize(std::ostream& os) const
{
    Tree<FamilyNode>::serialize(os);
}

void FamilyTree::deserialize(std::istream& is)
{
    Tree<FamilyNode>::deserialize(is);
}

void FamilyTree::save(const std::string& filename) const
{
    std::ofstream file;
    file.open(filename, std::ios::out | std::ios::binary);

    if(!file)
    {
        //TODO : Error info
        return;
    }

    serialize(file);
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

    drawLinkLines(root_, drawer);
}

FamilyTree::NodePtr FamilyTree::getNodeAtPosition(const NodePtr& root, const Point& pos) const
{
    if(root == nullptr)
        return nullptr;

    auto data = root->getValue();
    if(data.getFrame().contains(pos))
        return root;

    const auto& children = root->getChildren();
    for(const auto& child : children)
    {
        auto node = getNodeAtPosition(child, pos);
        if(node != nullptr)
            return node;
    }

    return nullptr;
}

bool FamilyTree::removeSubtreeAtPosition(NodePtr& root, const Point& pos)
{
    auto pred = [&pos](const auto& node)
    {
        return node->getValue().getFrame().contains(pos);
    };

    if(root == nullptr)
        return false;

    if(root->removeChild(pred))
        return true;

    auto& childern = root->getChildren();
    for(auto& child : childern)
    {
        if(removeSubtreeAtPosition(child, pos))
            return true;
    }

    return false;
}

Rect FamilyTree::getBoundingBox(const NodePtr& root) const
{
    Rect bb{};
    if(root == nullptr)
        return bb;

    bb = root->getValue().getFrame();
    root->doWithChildren([this, &bb] (const std::shared_ptr<Node>& child)
    {
        bb.unionWith(getBoundingBox(child));
    });

    return bb;
}

void FamilyTree::drawLinkLines(const NodePtr& root, Drawer& drawer) const
{
    if(root == nullptr || root->getChildren().empty())
        return;

    const auto& children = root->getChildren();
    Rect rootFrame = root->getValue().getFrame();
    Point rootBottomMidpoint = rootFrame.bottomMidpoint();

    for(const auto& child : children)
    {
        drawLinkLines(child, drawer);

        Rect childFrame = child->getValue().getFrame();
        drawer.drawLine(rootBottomMidpoint, childFrame.topMidpoint());
    }
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

#include "FamilyNode.h"

FamilyNode::FamilyNode(const PersonDataPtr& data, const Rect& frame) :
    data_(data), frame_(frame)

{

}

void FamilyNode::draw(Drawer& drawer)
{
    drawer.darwRect(frame_);
    data_->draw(drawer, frame_);
}

Rect& FamilyNode::getFrame()
{
    return frame_;
}

const Rect& FamilyNode::getFrame() const
{
    return frame_;
}

PersonDataPtr FamilyNode::getPersonData()
{
    return data_;
}

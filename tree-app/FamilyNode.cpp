#include "FamilyNode.h"

FamilyNode::FamilyNode(const PersonDataPtr& data, const Rect& frame) :
    data_(data), frame_(frame)

{

}

void FamilyNode::draw(Drawer& drawer)
{
    drawer.darwRect(frame_);
}

#include "FamilyNode.h"

FamilyNode::FamilyNode(const PersonDataPtr& data, const Rect& frame) :
    data_(data), frame_(frame)

{

}

FamilyNode FamilyNode::copy() const
{
    PersonDataPtr dataPtr = data_ != nullptr ? std::make_shared<PersonData>(*data_) : nullptr;

    return {dataPtr, frame_};
}

void FamilyNode::draw(Drawer& drawer)
{
    drawer.drawRect(frame_);

    if(data_ != nullptr)
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

void FamilyNode::serialize(std::ostream& os) const
{
    if(data_ != nullptr)
    {
        os << true;
        data_->serialize(os);
    }
    else
    {
        os << false;
    }

    frame_.serialize(os);
}

void FamilyNode::deserialize(std::istream& is)
{
    bool dataPresent;
    is >> dataPresent;
    if(dataPresent)
    {
        data_ = std::make_shared<PersonData>();
        data_->deserialize(is);
    }
    frame_.deserialize(is);
}


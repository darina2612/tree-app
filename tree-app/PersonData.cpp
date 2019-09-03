#include "PersonData.h"

#include "Rect.h"
#include "Drawer.h"
#include "SerializationUtils.h"

PersonData::PersonData(const std::string& name, const std::string& pictureFileName) :
                       name_(name),
                       picture_(pictureFileName)
{
}

void PersonData::setName(const std::string& name)
{
    name_ = name;
}

const std::string& PersonData::getName() const
{
    return name_;
}

void PersonData::setPicture(const std::string& pictureFileName)
{
    picture_ = Image(pictureFileName);
}

const Image& PersonData::getPicture() const
{
    return picture_;
}

void PersonData::draw(Drawer& drawer, const Rect& frame) const
{

    drawer.drawImage({frame.left() + 10, frame.top() + 10, frame.width() - 20, frame.height() - 50},
                     picture_);

    drawer.drawText({frame.left() + 10, frame.bottom() - 40, frame.width() - 20, 30}, name_);
}

void PersonData::serialize(std::ostream& os) const
{
    Serialization::serialize(os, name_);
    picture_.serialize(os);
}

void PersonData::deserialize(std::istream& is)
{
    Deserialization::deserialize(is, name_);
    picture_.deserialize(is);
}

#include "PersonData.h"

#include "Rect.h"
#include "Drawer.h"

PersonData::PersonData(const std::string& name, const std::string& pictureFileName) :
                       name_(name),
                       pictureFileName_(pictureFileName)
{
}

void PersonData::setName(const std::string& name)
{
    name_ = name;
}

void PersonData::setPictureFileName(const std::string& pictureFileName)
{
    pictureFileName_ = pictureFileName;
}

void PersonData::draw(Drawer& drawer, const Rect& frame) const
{

    drawer.drawImage({frame.left() + 10, frame.top() + 10, frame.width() - 20, frame.height() - 50},
                     pictureFileName_);

    drawer.drawText({frame.left() + 10, frame.bottom() - 40, frame.width() - 20, 30}, name_);

}

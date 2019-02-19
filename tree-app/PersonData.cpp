#include "PersonData.h"

#include "Rect.h"
#include "Drawer.h"

PersonData::PersonData(const std::string& name, const std::string& pictureFileName) :
                       name_(name),
                       pictureFileName_(pictureFileName)
{
}

void PersonData::draw(Drawer& drawer, const Rect& frame) const
{
    drawer.drawImage({frame.left() + 10, frame.top() + 10, frame.width() - 20, frame.height() - 20},
                     pictureFileName_);
}

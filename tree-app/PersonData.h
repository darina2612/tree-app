#pragma once

#include <string>
#include <memory>

class Drawer;
struct Rect;

class PersonData
{
public:
    PersonData() = default;
    PersonData(const std::string& name, const std::string& pictureFileName);

    void setName(const std::string& name);
    const std::string& getName() const;

    void setPictureFileName(const std::string& pictureFileName);
    const std::string& getPictureFileName() const;

    void draw(Drawer& drawer, const Rect& frame) const;

protected:
    std::string name_;
    std::string pictureFileName_;
};

using PersonDataPtr = std::shared_ptr<PersonData>;

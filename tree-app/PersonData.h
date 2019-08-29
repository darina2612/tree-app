#pragma once

#include <string>
#include <memory>
#include "Image.h"
#include <iostream>

class Drawer;
struct Rect;

class PersonData
{
public:
    PersonData() = default;
    PersonData(const std::string& name, const std::string& pictureFileName);

    void setName(const std::string& name);
    const std::string& getName() const;

    void setPicture(const std::string& pictureFileName);
    const Image& getPicture() const;

    void draw(Drawer& drawer, const Rect& frame) const;

    void serialize(std::ostream& os) const;
    void deserialize(std::istream& is);

protected:
    std::string name_;
    Image picture_;
};

using PersonDataPtr = std::shared_ptr<PersonData>;

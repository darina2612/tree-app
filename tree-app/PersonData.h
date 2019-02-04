#pragma once

#include <string>

class PersonData
{
public:
    PersonData(const std::string& name, const std::string& pictureFileName);

protected:
    std::string name_;
    std::string pictureFileName_;
};

#pragma once

#include <string>
#include <memory>

class PersonData
{
public:
    PersonData(const std::string& name, const std::string& pictureFileName);

protected:
    std::string name_;
    std::string pictureFileName_;
};

using PersonDataPtr = std::shared_ptr<PersonData>;

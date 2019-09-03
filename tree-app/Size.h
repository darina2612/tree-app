#pragma once
#include <iostream>
#include "SerializationUtils.h"

struct Size
{
    Size() = default;

    Size(int width, int height) : width_(width), height_(height)
    {
    }

    void serialize(std::ostream& os) const
    {
       Serialization::serialize(os, width_);
       Serialization::serialize(os, height_);
    }

    void deserialize(std::istream& is)
    {
        Deserialization::deserialize(is, width_);
        Deserialization::deserialize(is, height_);
    }

    int width_{};
    int height_{};
};

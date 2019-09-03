#pragma once
#include <fstream>
#include "SerializationUtils.h"

struct Point
{
    Point() = default;

    Point(int x, int y) : x_(x), y_(y)
    {
    }

    void serialize(std::ostream& os) const
    {
        Serialization::serialize(os, x_);
        Serialization::serialize(os, y_);
    }

    void deserialize(std::istream& is)
    {
        Deserialization::deserialize(is, x_);
        Deserialization::deserialize(is, y_);
    }

    int x_{};
    int y_{};
};

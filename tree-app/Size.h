#pragma once
#include <iostream>

struct Size
{
    Size(int width, int height) : width_(width), height_(height)
    {
    }

    void serialize(std::ostream& os) const
    {
        os << width_ << height_;
    }

    void deserialize(std::istream& is)
    {
        is >> width_ >> height_;
    }

    int width_;
    int height_;
};

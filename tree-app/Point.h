#pragma once
#include <fstream>

struct Point
{
    Point(int x, int y) : x_(x), y_(y)
    {
    }

    void serialize(std::ostream& os) const
    {
        os << x_ << y_;
    }

    void deserialize(std::istream& is)
    {
        is >> x_ >> y_;
    }

    int x_;
    int y_;
};

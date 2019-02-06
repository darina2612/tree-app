#pragma once

#include "Size.h"
#include "Point.h"

struct Rect
{
    Rect(int x, int y, int width, int height) : origin_(x, y), size_(width, height)
    {
    }

    int top()
    {
        return origin_.y_;
    }

    int left()
    {
        return origin_.x_;
    }

    int bottom()
    {
        return origin_.y_ + size_.height_;
    }

    int right()
    {
        return origin_.x_ + size_.width_;
    }

    Point origin_;
    Size size_;
};

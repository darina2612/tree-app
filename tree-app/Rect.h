#pragma once

#include "Size.h"
#include "Point.h"

struct Rect
{
    Rect(int x, int y, int width, int height) : origin_(x, y), size_(width, height)
    {
    }

    int top() const
    {
        return origin_.y_;
    }

    int left() const
    {
        return origin_.x_;
    }

    int bottom() const
    {
        return origin_.y_ + size_.height_;
    }

    int right() const
    {
        return origin_.x_ + size_.width_;
    }

    int width() const
    {
        return size_.width_;
    }

    int height() const
    {
        return size_.height_;
    }

    Point topMidpoint() const
    {
        return {origin_.x_ + (size_.width_ / 2), origin_.y_};
    }

    Point bottomMidpoint() const
    {
        return {origin_.x_ + (size_.width_ / 2), origin_.y_ + size_.height_};
    }

    bool contains(const Point& p) const
    {
        return p.x_ >= left() && p.x_ <= right() &&
               p.y_  >= top() && p.y_ <= bottom();
    }

    Point origin_;
    Size size_;
};

#pragma once

#include "Size.h"
#include "Point.h"
#include <iostream>
#include <algorithm>
#include "SerializationUtils.h"

struct Rect
{
    Rect(int x = 0, int y = 0, int width = 0, int height = 0) : origin_(x, y), size_(width, height)
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

    void unionWith(const Rect& other)
    {
        Point bottomRight{std::max(origin_.x_ + size_.width_,
                                   other.origin_.x_ + other.size_.width_),
                          std::max(origin_.y_ + size_.height_,
                                   other.origin_.y_ + other.size_.height_)};

        origin_ = {std::min(origin_.x_, other.origin_.x_),
                   std::min(origin_.y_, other.origin_.y_)};

        size_ = {abs(bottomRight.x_ - origin_.x_), abs(bottomRight.y_ - origin_.y_)};
    }

    void extendWith(const Size& size)
    {
        origin_.x_ -= size.width_ / 2;
        origin_.y_ -= size.height_ / 2;

        size_.width_ += size.width_;
        size_.height_ += size.height_;
    }

    void serialize(std::ostream& os) const
    {
        Serialization::serialize(os, origin_);
        Serialization::serialize(os, size_);
    }

    void deserialize(std::istream& is)
    {
        Deserialization::deserialize(is, origin_);
        Deserialization::deserialize(is, size_);
    }

    Point origin_;
    Size size_;
};

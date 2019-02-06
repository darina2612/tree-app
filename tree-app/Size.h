#pragma once

struct Size
{
    Size(int width, int height) : width_(width), height_(height)
    {
    }

    int width_;
    int height_;
};

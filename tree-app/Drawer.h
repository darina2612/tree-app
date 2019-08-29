#pragma once

#include <string>

class QPainter;
struct Rect;
struct Point;
class Image;

class Drawer
{
public:
    Drawer(QPainter* painter);

    void drawRect(const Rect& rect);

    void drawLine(const Point& point1, const Point& point2);

    void drawImage(const Rect& frame, const Image& image);

    void drawText(const Rect& frame, const std::string& text);

protected:
    QPainter* painter_;
};

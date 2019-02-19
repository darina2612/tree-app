#pragma once

#include <string>

class QPainter;
struct Rect;
struct Point;

class Drawer
{
public:
    Drawer(QPainter* painter);

    void darwRect(const Rect& rect);

    void darwLine(const Point& point1, const Point& point2);

    void drawImage(const Rect& frame, const std::string& filename);

protected:
    QPainter* painter_;
};

#pragma once

class QPainter;
struct Rect;
struct Point;

class Drawer
{
public:
    Drawer(QPainter* painter);

    void darwRect(const Rect& rect);

    void darwLine(const Point& point1, const Point& point2);

protected:
    QPainter* painter_;
};

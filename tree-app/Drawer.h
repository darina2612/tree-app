#pragma once

class QPainter;
struct Rect;

class Drawer
{
public:
    Drawer(QPainter* painter);

    void darwRect(const Rect& rect);

protected:
    QPainter* painter_;
};

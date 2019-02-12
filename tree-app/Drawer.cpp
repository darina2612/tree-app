#include "Drawer.h"

#include "Rect.h"
#include <cassert>
#include <QPainter>
#include <ConversionUtils.h>

Drawer::Drawer(QPainter* painter) : painter_(painter)
{
}

void Drawer::darwRect(const Rect& rect)
{
    if(painter_ == nullptr)
    {
        assert(false);
        return;
    }

    painter_->drawRect(ConversionUtils::qRectFromRect(rect));
}

void Drawer::darwLine(const Point& point1, const Point& point2)
{
    if(painter_ == nullptr)
    {
        assert(false);
        return;
    }

    painter_->drawLine(ConversionUtils::qPointFromPoint(point1),
                       ConversionUtils::qPointFromPoint(point2));
}


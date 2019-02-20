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

void Drawer::drawImage(const Rect& frame, const std::string& filename)
{
    if(painter_ == nullptr)
    {
        assert(false);
        return;
    }

    QImage qImage(filename.c_str());

    painter_->drawImage(ConversionUtils::qRectFromRect(frame), qImage);
}

void Drawer::drawText(const Rect& frame, const std::string& text)
{
    if(painter_ == nullptr)
    {
        assert(false);
        return;
    }

    QString qStr(text.c_str());

    painter_->drawText(ConversionUtils::qRectFromRect(frame), qStr);
}



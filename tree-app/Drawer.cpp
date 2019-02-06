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

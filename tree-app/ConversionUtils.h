#pragma once

#include <QRect>
#include <QSize>
#include "Rect.h"
#include "Size.h"
#include <QPoint>
#include "Point.h"

namespace ConversionUtils
{
    Point pointFromQPoint(const QPoint& qPoint);
    QPoint qPointFromPoint(const Point& point);

    Size sizeFromQSize(const QSize& qSize);
    QSize qSizeFromSize(const Size& size);

    Rect rectFromQRect(const QRect& qRect);
    QRect qRectFromRect(const Rect& rect);
}

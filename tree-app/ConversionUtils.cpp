#include "ConversionUtils.h"

namespace ConversionUtils
{
    Point pointFromQPoint(const QPoint& qPoint)
    {
        return {qPoint.x(), qPoint.y()};
    }

    QPoint qPointFromPoint(const Point& point)
    {
        return {point.x_, point.y_};
    }

    Size sizeFromQSize(const QSize& qSize)
    {
        return {qSize.width(), qSize.height()};
    }

    QSize qSizeFromSize(const Size& size)
    {
        return {size.width_, size.height_};
    }

    Rect rectFromQRect(const QRect& qRect)
    {
        return {qRect.x(), qRect.y(), qRect.width(), qRect.height()};
    }

    QRect qRectFromRect(const Rect& rect)
    {
        return {qPointFromPoint(rect.origin_), qSizeFromSize(rect.size_)};
    }
}

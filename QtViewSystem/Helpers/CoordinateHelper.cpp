#include "CoordinateHelper.h"


CoordinateHelper::CoordinateInfo::CoordinateInfo(): CoordinateInfo({0, 0, 0, 0})
{}

CoordinateHelper::CoordinateInfo::CoordinateInfo(float x1, float y1, float x2, float y2): CoordinateInfo({x1, y1, x2, y2})
{}

CoordinateHelper::CoordinateInfo::CoordinateInfo(const QRectF &r):
    rect(r.topLeft().x(), r.topLeft().y(), r.width(), r.height()),
    rectTopLeft(r.topLeft().x(), r.topLeft().y()),
    rectBottomRight(QPointF{r.width(), r.height()}),
    rectSize(QSizeF{rectBottomRight.x() - rectTopLeft.x(), rectBottomRight.y() - rectTopLeft.y()}),
    rectWidth(rectSize.width()),
    rectHeight(rectSize.height()),
    clipRect(QRectF{0, 0, rectSize.width(), rectSize.height()})
{}

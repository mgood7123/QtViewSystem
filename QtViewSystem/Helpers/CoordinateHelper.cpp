#include "CoordinateHelper.h"


CoordinateHelper::CoordinateInfo::CoordinateInfo(): CoordinateInfo({0, 0, 0, 0})
{}

CoordinateHelper::CoordinateInfo::CoordinateInfo(int x1, int y1, int x2, int y2): CoordinateInfo({x1, y1, x2, y2})
{}

CoordinateHelper::CoordinateInfo::CoordinateInfo(const QRect &r):
    rect(r.topLeft().x(), r.topLeft().y(), r.width(), r.height()),
    rectTopLeft(r.topLeft().x(), r.topLeft().y()),
    rectBottomRight(QPoint{r.width(), r.height()}),
    rectSize(QSize{rectBottomRight.x() - rectTopLeft.x(), rectBottomRight.y() - rectTopLeft.y()}),
    rectWidth(rectSize.width()),
    rectHeight(rectSize.height())
{}

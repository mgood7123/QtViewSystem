#include "CoordinateHelper.h"


CoordinateHelper::CoordinateInfo::CoordinateInfo(): CoordinateInfo(0, 0, 0, 0)
{}

CoordinateHelper::CoordinateInfo::CoordinateInfo(int x1, int y1, int x2, int y2): CoordinateInfo({x1, y1, x2, y2})
{}

CoordinateHelper::CoordinateInfo::CoordinateInfo(const QRect &r):
    topLeftX(r.x()),
    topLeftY(r.y()),
    bottomRightX(r.width()),
    bottomRightY(r.height()),
    width(r.width() - r.x()),
    height(r.height() - r.y())
{}

QRect CoordinateHelper::CoordinateInfo::toQRect() {
    return QRect(topLeftX, topLeftY, width, height);
}

QDebug operator<<(QDebug debug, const CoordinateHelper::CoordinateInfo &c)
{
    QDebugStateSaver saver(debug);
    debug.nospace() << "CoordinateInfo(" << c.topLeftX << "," << c.topLeftY << " " << c.bottomRightX << "x" << c.bottomRightY << ')';
    return debug;
}

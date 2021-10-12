#include "CoordinateHelper.h"


CoordinateHelper::CoordinateInfo::CoordinateInfo(): CoordinateInfo(0, 0, 0, 0)
{}

CoordinateHelper::CoordinateInfo::CoordinateInfo(float x1, float y1, float x2, float y2): CoordinateInfo({x1, y1, x2, y2})
{}

CoordinateHelper::CoordinateInfo::CoordinateInfo(const QRectF &r):
    topLeftX(r.x()),
    topLeftY(r.y()),
    bottomRightX(r.width()),
    bottomRightY(r.height()),
    width(r.width() - r.x()),
    height(r.height() - r.y())
{}

QRectF CoordinateHelper::CoordinateInfo::toQRectF() {
    return QRectF(topLeftX, topLeftY, width, height);
}

QDebug operator<<(QDebug debug, const CoordinateHelper::CoordinateInfo &c)
{
    QDebugStateSaver saver(debug);
    debug.nospace() << "CoordinateInfo(" << c.topLeftX << "," << c.topLeftY << " " << c.bottomRightX << "x" << c.bottomRightY << ')';
    return debug;
}

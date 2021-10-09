#ifndef COORDINATEHELPER_H
#define COORDINATEHELPER_H

#include <QDebug>
#include <QRectF>

class CoordinateHelper
{
public:
    struct CoordinateInfo {
        int topLeftX;
        int topLeftY;
        int bottomRightX;
        int bottomRightY;
        int width;
        int height;
        CoordinateInfo();
        explicit CoordinateInfo(int x1, int y1, int x2, int y2);
        CoordinateInfo(const QRect & r);
        QRect toQRect();
    };

    CoordinateInfo relativeCoordinates;
    CoordinateInfo absoluteCoordinates;
};

QDebug operator<<(QDebug debug, const CoordinateHelper::CoordinateInfo &c);

#endif // COORDINATEHELPER_H

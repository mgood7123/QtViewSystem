#ifndef COORDINATEHELPER_H
#define COORDINATEHELPER_H

#include <QDebug>
#include <QRectF>

class CoordinateHelper
{
public:
    struct CoordinateInfo {
        float topLeftX;
        float topLeftY;
        float bottomRightX;
        float bottomRightY;
        float width;
        float height;
        CoordinateInfo();
        explicit CoordinateInfo(float x1, float y1, float x2, float y2);
        CoordinateInfo(const QRectF & r);
        QRectF toQRectF();
    };

    CoordinateInfo relativeCoordinates;
    CoordinateInfo absoluteCoordinates;
};

QDebug operator<<(QDebug debug, const CoordinateHelper::CoordinateInfo &c);

#endif // COORDINATEHELPER_H

#ifndef COORDINATEHELPER_H
#define COORDINATEHELPER_H

#include <QRectF>



class CoordinateHelper
{
public:
    struct CoordinateInfo {
        QRectF rect;
        QPointF rectTopLeft;
        QPointF rectBottomRight;
        QSizeF rectSize;
        qreal rectWidth;
        qreal rectHeight;
        QRectF clipRect;
        CoordinateInfo();;
        explicit CoordinateInfo(float x1, float y1, float x2, float y2);;
        CoordinateInfo(const QRectF & r);;
    };

    CoordinateInfo relativeCoordinates;
    CoordinateInfo absoluteCoordinates;
};

#endif // COORDINATEHELPER_H

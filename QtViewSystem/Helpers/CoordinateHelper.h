#ifndef COORDINATEHELPER_H
#define COORDINATEHELPER_H

#include <QRectF>



class CoordinateHelper
{
public:
    struct CoordinateInfo {
        QRect rect;
        QPoint rectTopLeft;
        QPoint rectBottomRight;
        QSize rectSize;
        int rectWidth;
        int rectHeight;
        QRect clipRect;
        CoordinateInfo();;
        explicit CoordinateInfo(int x1, int y1, int x2, int y2);;
        CoordinateInfo(const QRect & r);;
    };

    CoordinateInfo relativeCoordinates;
    CoordinateInfo absoluteCoordinates;
};

#endif // COORDINATEHELPER_H

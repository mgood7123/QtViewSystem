#ifndef QTOPENGLVIEWSYSTEMWINDOWDATA_H
#define QTOPENGLVIEWSYSTEMWINDOWDATA_H

#include <QWindow>
#include <QScreen>

class QTOpenGLViewSystemWindowData
{
public:
    QWindow * window = nullptr;
    QScreen * screen = nullptr;
    qreal dpiScale = 1;
};

#endif // QTOPENGLVIEWSYSTEMWINDOWDATA_H

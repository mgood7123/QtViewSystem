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

    int applyDpiScale(qreal value) const;

    int applyDpiScale(int value) const;

    qreal applyDpiScaleF(qreal value) const;

    qreal applyDpiScaleF(int value) const;
};

#endif // QTOPENGLVIEWSYSTEMWINDOWDATA_H

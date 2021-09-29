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

    inline int applyDpiScale(qreal value) const {
        return static_cast<int>(dpiScale * value);
    }

    inline int applyDpiScale(int value) const {
        return applyDpiScale(qreal(value));
    }

    inline qreal applyDpiScaleF(qreal value) const {
        return dpiScale * value;
    }

    inline qreal applyDpiScaleF(int value) const {
        return applyDpiScaleF(qreal(value));
    }
};

#endif // QTOPENGLVIEWSYSTEMWINDOWDATA_H

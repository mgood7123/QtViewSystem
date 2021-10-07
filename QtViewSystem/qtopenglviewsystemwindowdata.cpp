#include <qtopenglviewsystemwindowdata.h>

int QTOpenGLViewSystemWindowData::applyDpiScale(qreal value) const {
    return static_cast<int>(dpiScale * value);
}

int QTOpenGLViewSystemWindowData::applyDpiScale(int value) const {
    return applyDpiScale(qreal(value));
}

qreal QTOpenGLViewSystemWindowData::applyDpiScaleF(qreal value) const {
    return dpiScale * value;
}

qreal QTOpenGLViewSystemWindowData::applyDpiScaleF(int value) const {
    return applyDpiScaleF(qreal(value));
}

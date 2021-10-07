#ifndef WINDOWDATAHELPER_H
#define WINDOWDATAHELPER_H

#include <qtopenglviewsystemwindowdata.h>

class WindowDataHelper {
    // points to read-only data managed by QTOpenGLViewSystem
    const QTOpenGLViewSystemWindowData * windowData = nullptr;

public:
    virtual void setWindowData(const QTOpenGLViewSystemWindowData * windowData);

    const QTOpenGLViewSystemWindowData * getWindowData();

    int applyDpiScale(qreal value) const;

    int applyDpiScale(int value) const;

    qreal applyDpiScaleF(qreal value) const;

    qreal applyDpiScaleF(int value) const;
};

#endif // WINDOWDATAHELPER_H

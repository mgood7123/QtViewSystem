#include "WindowDataHelper.h"

void WindowDataHelper::setWindowData(const QTOpenGLViewSystemWindowData *windowData) {
    this->windowData = windowData;
}

const QTOpenGLViewSystemWindowData *WindowDataHelper::getWindowData() {
    return windowData;
}

int WindowDataHelper::applyDpiScale(qreal value) const {
    if (windowData == nullptr) qFatal("cannot apply dpi scale with no window data");
    return windowData->applyDpiScale(value);
}

int WindowDataHelper::applyDpiScale(int value) const {
    if (windowData == nullptr) qFatal("cannot apply dpi scale with no window data");
    return windowData->applyDpiScale(value);
}

qreal WindowDataHelper::applyDpiScaleF(qreal value) const {
    if (windowData == nullptr) qFatal("cannot apply dpi scale with no window data");
    return windowData->applyDpiScale(value);
}

qreal WindowDataHelper::applyDpiScaleF(int value) const {
    if (windowData == nullptr) qFatal("cannot apply dpi scale with no window data");
    return windowData->applyDpiScale(value);
}

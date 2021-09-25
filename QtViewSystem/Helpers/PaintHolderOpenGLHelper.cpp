#include "PaintHolderOpenGLHelper.h"

QOpenGLContext *PaintHolderOpenGLHelper::getOpenGLContext() {
    if (paintHolder.painter != nullptr) {
        return paintHolder.paintDevice->context();
    }
    return nullptr;
}

QOpenGLFunctions *PaintHolderOpenGLHelper::getOpenGLFunctions() {
    QOpenGLContext * context = getOpenGLContext();
    if (context != nullptr) {
        return context->functions();
    }
    return nullptr;
}

QOpenGLExtraFunctions *PaintHolderOpenGLHelper::getOpenGLExtraFunctions() {
    QOpenGLContext * context = getOpenGLContext();
    if (context != nullptr) {
        return context->extraFunctions();
    }
    return nullptr;
}

#include "opengl_view.h"

QSize OpenGL_View::getWindowSize() { return paintHolder.getSize(); }

int OpenGL_View::getWindowWidth() { return getWindowSize().width(); }

int OpenGL_View::getWindowHeight() { return getWindowSize().height(); }

OpenGL_View::OpenGL_View() {}

OpenGL_View::~OpenGL_View() {
    delete layoutParams;
}

OpenGL_View::LayoutParams *OpenGL_View::getLayoutParams() const {
    return layoutParams;
}

void OpenGL_View::setLayoutParams(LayoutParams *params) {
    // important optimization:
    // if params are self, then
    //   do not delete layoutParams
    //     it will invalidate/corrupt the passed params
    //     since it points to layoutParams, resulting in use-after-free
    //
    //   avoid this useless assignment:
    //     LayoutParams * params = layoutParams;
    //     layoutParams = params;
    if (params != layoutParams) {
        delete layoutParams;
        layoutParams = params;
    }
}

void OpenGL_View::measure(int width, int height)
{
    measuredDimensions = INVALID_MEASUREMENT_DIMENSION;
    onMeasure(width, height);
    if (measuredDimensions == INVALID_MEASUREMENT_DIMENSION) {
        qFatal("invalid measurement, did you forget to call setMeasuredDimensions(const QSize &); ?");
    }
}

void OpenGL_View::setMeasuredDimensions(int width, int height)
{
    setMeasuredDimensions({width, height});
}

void OpenGL_View::setMeasuredDimensions(const QSize &size)
{
    measuredDimensions = size;
}

QSize OpenGL_View::getMeasuredDimensions()
{
    return measuredDimensions;
}

int OpenGL_View::getMeasuredWidth()
{
    return measuredDimensions.width();
}

int OpenGL_View::getMeasuredHeight()
{
    return measuredDimensions.height();
}

void OpenGL_View::onMeasure(int width, int height)
{
    LayoutParams * params = getLayoutParams();
    QSize measuredDimensions = QSize{params->width, params->height};
    if (params->width == MATCH_PARENT) {
        measuredDimensions.setWidth(width);
    } else if (params->width == WRAP_CONTENT) {
        measuredDimensions.setWidth(0);
    }
    if (params->height == MATCH_PARENT) {
        measuredDimensions.setHeight(height);
    } else if (params->height == WRAP_CONTENT) {
        measuredDimensions.setHeight(0);
    }
    setMeasuredDimensions(measuredDimensions);
}

void OpenGL_View::onResizeGL(QSize window_size) {
    onResizeGL(window_size.width(), window_size.height());
}

void OpenGL_View::onResizeGL(int window_w, int window_h) {
    paintHolder.resize(window_w, window_h);
}

void OpenGL_View::onAddedToLayout()
{

}

void OpenGL_View::onRemovedFromLayout()
{

}

void OpenGL_View::onPaintGL() {}

bool OpenGL_View::isLayout() const {
    return false;
}

void OpenGL_View::setGLViewport(GLint x, GLint y, GLsizei width, GLsizei height) {
    if (paintHolder.glES3Functions != nullptr) {
        paintHolder.glES3Functions->glViewport(x, y, width, height);
    }
}

void OpenGL_View::setGLViewport(const QRect &widthHeightCoordinates) {
    setGLViewport(widthHeightCoordinates.x(), widthHeightCoordinates.y(), widthHeightCoordinates.width(), widthHeightCoordinates.height());
}

void OpenGL_View::buildCoordinates(const QRect &relativeCoordinates) {
    this->relativeCoordinates = relativeCoordinates;
    if (parent == nullptr) {
        absoluteCoordinates = this->relativeCoordinates;
    } else {
        absoluteCoordinates = CoordinateInfo(relativeCoordinates.translated(parent->absoluteCoordinates.rectTopLeft));
    }
}

OpenGL_View::LayoutParams::LayoutParams(int width, int height) : width(width), height(height) {}

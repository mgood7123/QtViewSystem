#include "opengl_view.h"

QSizeF OpenGL_View::getSize() { return paintHolder.getSize(); }

int OpenGL_View::getWidth() { return getSize().width(); }

int OpenGL_View::getHeight() { return getSize().height(); }

OpenGL_View::OpenGL_View() {}

OpenGL_View::~OpenGL_View() {
    delete layoutParams;
}

void OpenGL_View::onResize(const QSizeF & size) {
    onResize(size.width(), size.height());
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

void OpenGL_View::measure()
{
    measuredDimensions = INVALID_MEASUREMENT_DIMENSION;
    onMeasure();
    if (measuredDimensions == INVALID_MEASUREMENT_DIMENSION) {
        qFatal("invalid measurement, did you forget to call setMeasuredDimensions(const QSize &); ?");
    }

}

void OpenGL_View::setMeasuredDimensions(const QSizeF &size)
{
    measuredDimensions = size;
}

QSizeF OpenGL_View::getMeasuredDimensions()
{
    return measuredDimensions;
}

qreal OpenGL_View::getMeasuredWidth()
{
    return measuredDimensions.width();
}

qreal OpenGL_View::getMeasuredHeight()
{
    return measuredDimensions.height();
}

void OpenGL_View::onMeasure()
{
    setMeasuredDimensions({0, 0});
}

void OpenGL_View::layout(const QRectF &dimensions)
{
    layoutData = dimensions;
    bool changed = false;
    if (cache_layoutData != layoutData) {
        cache_layoutData = layoutData;
        changed = true;
    }
    onLayout(changed, layoutData);
}

void OpenGL_View::onLayout(bool changed, const QRectF &dimensions)
{
    Q_UNUSED(changed);
    Q_UNUSED(dimensions);
}

void OpenGL_View::onResize(qreal w, qreal h) {
    paintHolder.resize(w, h);
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

void OpenGL_View::buildCoordinates(const QRectF &relativeCoordinates) {
    this->relativeCoordinates = relativeCoordinates;
    if (parent == nullptr) {
        absoluteCoordinates = this->relativeCoordinates;
    } else {
        absoluteCoordinates = CoordinateInfo(relativeCoordinates.translated(parent->absoluteCoordinates.rectTopLeft));
    }
}

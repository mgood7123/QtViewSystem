#include "opengl_layerlayout.h"

void OpenGL_LayerLayout::onMeasure(int width, int height)
{
    for (OpenGL_View *view : children) {
        view->buildCoordinates({0, 0, width, height});
        view->measure(width, height);
    }
    setMeasuredDimensions(width, height);
}

void OpenGL_LayerLayout::onResizeGL(int window_w, int window_h)
{
    for (OpenGL_View * view: children) {
        view->onResizeGL(window_w, window_h);
    }
}

#include "opengl_layerlayout.h"

void OpenGL_LayerLayout::onMeasure(int width, int height)
{
    if (width == 0 || height == 0) {
        setMeasuredDimensions(0, 0);
        return;
    }
    for (OpenGL_View *view : children) {
        view->buildCoordinates({0, 0, width, height});
        view->measure(width, height);
    }
    setMeasuredDimensions(width, height);
}

#include "opengl_layerlayout.h"

void OpenGL_LayerLayout::onResize(qreal w, qreal h)
{
    for (OpenGL_View * view: children) {
        view->onResize(w, h);
    }
}

void OpenGL_LayerLayout::onPaintGL()
{
    for (OpenGL_View * view: children) {
        view->onPaintGL();
    }
}

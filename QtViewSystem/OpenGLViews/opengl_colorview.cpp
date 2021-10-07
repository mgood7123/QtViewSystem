#include "opengl_colorview.h"

const QColor &OpenGL_ColorView::getColor() const
{
    return color;
}

void OpenGL_ColorView::setColor(const QColor &newColor)
{
    color = newColor;
}

OpenGL_ColorView::OpenGL_ColorView(QColor color)
{
    this->color = color;
}


void OpenGL_ColorView::onPaintGL(QPainter *painter, QImage * paintDeviceQImage, GLuint *defaultFBO)
{
    auto * gl = getOpenGLExtraFunctions();
    painter->beginNativePainting();
    gl->glClearColor(color.red(), color.green(), color.blue(), color.alpha());
    gl->glClear(GL_COLOR_BUFFER_BIT);
    painter->endNativePainting();
}

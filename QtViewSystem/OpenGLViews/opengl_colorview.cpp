#include "opengl_colorview.h"

const QColor &OpenGL_ColorView::getColor() const
{
    return color;
}

void OpenGL_ColorView::setColor(const QColor &newColor)
{
    color = newColor;
}

OpenGL_ColorView::OpenGL_ColorView(float r, float g, float b)
{
    this->color.setRgbF(r, g, b, 1);
}

OpenGL_ColorView::OpenGL_ColorView(float r, float g, float b, float a)
{
    this->color.setRgbF(r, g, b, a);
}

OpenGL_ColorView::OpenGL_ColorView(QColor color)
{
    this->color = color;
}


void OpenGL_ColorView::onPaintGL(QPainter *painter, GLuint *defaultFBO)
{
    auto * gl = getOpenGLExtraFunctions();
    painter->beginNativePainting();
    gl->glClearColor(color.redF(), color.greenF(), color.blueF(), color.alphaF());
    gl->glClear(GL_COLOR_BUFFER_BIT);
    painter->endNativePainting();
}

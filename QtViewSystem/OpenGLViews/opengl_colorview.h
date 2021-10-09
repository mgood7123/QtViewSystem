#ifndef OPENGL_COLORVIEW_H
#define OPENGL_COLORVIEW_H


#include "opengl_view.h"

class OpenGL_ColorView : public OpenGL_View
{
    QColor color;
public:
    OpenGL_ColorView(float r, float g, float b);
    OpenGL_ColorView(float r, float g, float b, float a);
    OpenGL_ColorView(QColor color);

    const QColor &getColor() const;
    void setColor(const QColor &newColor);



    // OpenGL_View interface
private:
    virtual void onPaintGL(QPainter *painter, GLuint *defaultFBO) override;
};

#endif // OPENGL_COLORVIEW_H

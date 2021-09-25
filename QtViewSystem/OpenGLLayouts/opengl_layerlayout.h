#ifndef OPENGL_LAYERLAYOUT_H
#define OPENGL_LAYERLAYOUT_H

#include "opengl_layout.h"

class OpenGL_LayerLayout : public OpenGL_Layout
{
public:
    // OpenGL_View interface
public:
    virtual void onResize(qreal w, qreal h) override;
    virtual void onPaintGL() override;
};

#endif // OPENGL_LAYERLAYOUT_H

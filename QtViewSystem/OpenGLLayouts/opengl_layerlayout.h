#ifndef OPENGL_LAYERLAYOUT_H
#define OPENGL_LAYERLAYOUT_H

#include "opengl_layout.h"

class OpenGL_LayerLayout : public OpenGL_Layout
{
public:

    // OpenGL_View interface
public:
    virtual void onMeasure(int width, int height) override;
};

#endif // OPENGL_LAYERLAYOUT_H

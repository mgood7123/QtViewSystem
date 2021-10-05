#ifndef OPENGL_LINEARLAYOUT_H
#define OPENGL_LINEARLAYOUT_H

#include "opengl_layout.h"

class OpenGL_LinearLayout : public OpenGL_Layout
{
public:
    enum Orientation {
        Horizontal, Vertical
    };
private:
    Orientation orientation = Vertical;
public:
    class LinearLayoutParams : public OpenGL_View::LayoutParams {
    public:
        // constructors
        using OpenGL_View::LayoutParams::LayoutParams;
        float weight = 1;
    };

    // OpenGL_View interface
public:
    virtual void onMeasure(int width, int height) override;
};

#endif // OPENGL_LINEARLAYOUT_H

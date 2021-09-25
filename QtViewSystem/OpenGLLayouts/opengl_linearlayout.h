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

    class LinearLayoutParams : public LayoutParams {
    public:
        float weight;
        LinearLayoutParams() : weight(1.0f) {}
        LinearLayoutParams(float weight) : weight(weight) {}
        LinearLayoutParams(GRAVITY gravity, float weight) : LayoutParams(gravity), weight(weight) {}
    };

    // OpenGL_View interface
public:
    virtual void onMeasure() override;
    virtual void onLayout(bool changed, const QRectF &dimensions) override;
};

#endif // OPENGL_LINEARLAYOUT_H

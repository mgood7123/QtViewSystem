#ifndef OPENGL_LAYOUT_H
#define OPENGL_LAYOUT_H

#include <OpenGLViews/opengl_view.h>

class OpenGL_Layout : public OpenGL_View
{
public:
    virtual ~OpenGL_Layout();
    QList<OpenGL_View*> children;

    void addChild(OpenGL_View * view);
    void addChild(OpenGL_View * view, LayoutParams * params);

    void detachChild(OpenGL_View * view);

    void removeChild(OpenGL_View * view);

    void removeAllChildren();


    // OpenGLView interface
private:
    virtual void onPaintGL(QPainter * painter, QOpenGLFramebufferObject * defaultFBO) override;
public:
    virtual void onResizeGL(int window_w, int window_h) override;
    virtual bool isLayout() const override final;
};

#endif // OPENGL_LAYOUT_H

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
protected:
    virtual void onPaintGL(QPainter * painter, GLuint * defaultFBO) override;
public:
    virtual bool isLayout() const override final;

    // WindowDataHelper interface
public:
    virtual void setWindowData(const QTOpenGLViewSystemWindowData *windowData) override;
};

#endif // OPENGL_LAYOUT_H

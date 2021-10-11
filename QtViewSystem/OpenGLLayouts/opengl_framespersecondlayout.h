#ifndef OPENGL_FRAMESPERSECONDLAYOUT_H
#define OPENGL_FRAMESPERSECONDLAYOUT_H

#include "opengl_layerlayout.h"

class OpenGL_FramesPerSecondLayout : public OpenGL_LayerLayout
{
    ChronoTimer frameTime;
    ChronoTimer fpsUpdateTime;
    ChronoTimer lastFrameTime;

    quint64 frames = 0;
    float fps = 0;

    QList<float> fpsContainer;
    float N = 0;
    float avg_scale = 10;
    float exponential_fps = 0;

    int textSize;
    QColor textColor;
public:
    OpenGL_FramesPerSecondLayout();
    OpenGL_FramesPerSecondLayout(const int &textSize);
    OpenGL_FramesPerSecondLayout(const QColor &textColor);
    OpenGL_FramesPerSecondLayout(const int &textSize, const QColor &textColor);

    int getTextSize() const;
    void setTextSize(int newTextSize);

    const QColor &getTextColor() const;
    void setTextColor(const QColor &newTextColor);



    // OpenGL_View interface
protected:
    virtual void onPaintGL(QPainter *painter, GLuint *defaultFBO) override;
public:
    virtual void paintGLToFBO(int w, int h, GLuint *defaultFBO) override;
};

#endif // OPENGL_FRAMESPERSECONDLAYOUT_H

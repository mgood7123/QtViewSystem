#ifndef OPENGL_TEXTVIEW_H
#define OPENGL_TEXTVIEW_H

#include "opengl_view.h"

class OpenGL_TextView : public OpenGL_View
{
protected:
    QString text;
    int textSize;
    QColor textColor;
public:

    OpenGL_TextView();
    OpenGL_TextView(const QString &text);
    OpenGL_TextView(const int &textSize);
    OpenGL_TextView(const QColor &textColor);
    OpenGL_TextView(const int &textSize, const QColor &textColor);
    OpenGL_TextView(const QString &text, const int &textSize);
    OpenGL_TextView(const QString &text, const QColor &textColor);
    OpenGL_TextView(const QString &text, const int &textSize, const QColor &textColor);

    const QString &getText() const;
    void setText(const QString &newText);

    int getTextSize() const;
    void setTextSize(int newTextSize);

    const QColor &getTextColor() const;
    void setTextColor(const QColor &newTextColor);

    // OpenGLView interface
private:
    virtual void onPaintGL(QPainter * painter, QOpenGLFramebufferObject * defaultFBO) override;
};

#endif // OPENGL_TEXTVIEW_H

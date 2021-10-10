#ifndef OPENGL_BUTTONVIEW_H
#define OPENGL_BUTTONVIEW_H

#include "opengl_textview.h"

class OpenGL_ButtonView : public OpenGL_View
{
protected:
    QString text;
    int textSize;
    QColor textColor;
    QPicture recording;
    QRect lastW;
    QImage image;
public:

    OpenGL_ButtonView();
    OpenGL_ButtonView(const QString &text);
    OpenGL_ButtonView(const int &textSize);
    OpenGL_ButtonView(const QColor &textColor);
    OpenGL_ButtonView(const int &textSize, const QColor &textColor);
    OpenGL_ButtonView(const QString &text, const int &textSize);
    OpenGL_ButtonView(const QString &text, const QColor &textColor);
    OpenGL_ButtonView(const QString &text, const int &textSize, const QColor &textColor);

    const QString &getText() const;
    void setText(const QString &newText);

    int getTextSize() const;
    void setTextSize(int newTextSize);

    const QColor &getTextColor() const;
    void setTextColor(const QColor &newTextColor);

    // OpenGL_View interface // gets called from QOpenGLWindow
private:
    virtual void onPaintGL(QPainter *painter, GLuint *defaultFBO) override;
};

#endif // OPENGL_BUTTONVIEW_H

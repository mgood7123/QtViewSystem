#ifndef OPENGL_TEXTVIEW_H
#define OPENGL_TEXTVIEW_H

#include "opengl_view.h"

class OpenGL_TextView : public OpenGL_View
{
public:
    ANIMATION_GROUP_HELPER_PUBLIC_BASE(OpenGL_TextView);
private:
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

    // OpenGLView interface
public:


    virtual void onPaintGL() override;

    const QString &getText() const;
    OpenGL_TextView * setText(const QString &newText);
    int getTextSize() const;
    OpenGL_TextView * setTextSize(int newTextSize);
    const QColor &getTextColor() const;
    OpenGL_TextView * setTextColor(const QColor &newTextColor);

    // OpenGL_View interface
public:
    virtual void onAddedToLayout() override;
    virtual void onRemovedFromLayout() override;
};

#endif // OPENGL_TEXTVIEW_H

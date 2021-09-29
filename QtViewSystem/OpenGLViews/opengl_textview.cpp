#include "opengl_textview.h"

#include <QTimer>

const QString &OpenGL_TextView::getText() const
{
    return text;
}

OpenGL_TextView * OpenGL_TextView::setText(const QString &newText)
{
    text = newText;
    return this;
}

int OpenGL_TextView::getTextSize() const
{
    return textSize;
}

OpenGL_TextView * OpenGL_TextView::setTextSize(int newTextSize)
{
    textSize = newTextSize;
    return this;
}

const QColor &OpenGL_TextView::getTextColor() const
{
    return textColor;
}

OpenGL_TextView * OpenGL_TextView::setTextColor(const QColor &newTextColor)
{
    textColor = newTextColor;
    return this;
}

OpenGL_TextView::OpenGL_TextView() : OpenGL_TextView(13) {}

OpenGL_TextView::OpenGL_TextView(const QString &text) : OpenGL_TextView(text, 13) {}

OpenGL_TextView::OpenGL_TextView(const int &textSize) : OpenGL_TextView(textSize, QColorConstants::White) {}

OpenGL_TextView::OpenGL_TextView(const QColor &textColor) : OpenGL_TextView(13, textColor) {}

OpenGL_TextView::OpenGL_TextView(const int &textSize, const QColor &textColor) : OpenGL_TextView("OpenGLTextView", textSize, textColor) {}

OpenGL_TextView::OpenGL_TextView(const QString &text, const int &textSize) : OpenGL_TextView(text, textSize, QColorConstants::White) {}

OpenGL_TextView::OpenGL_TextView(const QString &text, const QColor &textColor) : OpenGL_TextView(text, 13, textColor) {}

OpenGL_TextView::OpenGL_TextView(const QString &text, const int &textSize, const QColor &textColor) : text(text), textSize(textSize), textColor(textColor) {}

void OpenGL_TextView::onPaintGL()
{
    auto * painter = paintHolder.painter;
    QFont f = painter->font();
    f.setPixelSize(textSize);
    painter->setFont(f);
    painter->setPen(textColor);
    painter->drawText(painter->window(), text);
}

void OpenGL_TextView::onAddedToLayout()
{
    // 120.000048 fps
    timeEngine.physicsTimeStep = 0.01666666/2;
    timeEngine.physicsCallback = [&](const TimeEngine & timeEngine_) {
    };
//    startAnimation();
}

void OpenGL_TextView::onRemovedFromLayout()
{
//    stopAnimation();
}

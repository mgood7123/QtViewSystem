#include "opengl_textview.h"

OpenGL_TextView::OpenGL_TextView() : OpenGL_TextView(13) {}

OpenGL_TextView::OpenGL_TextView(const QString &text) : OpenGL_TextView(text, 13) {}

OpenGL_TextView::OpenGL_TextView(const int &textSize) : OpenGL_TextView(textSize, QColorConstants::White) {}

OpenGL_TextView::OpenGL_TextView(const QColor &textColor) : OpenGL_TextView(13, textColor) {}

OpenGL_TextView::OpenGL_TextView(const int &textSize, const QColor &textColor) : OpenGL_TextView("OpenGLTextView", textSize, textColor) {}

OpenGL_TextView::OpenGL_TextView(const QString &text, const int &textSize) : OpenGL_TextView(text, textSize, QColorConstants::White) {}

OpenGL_TextView::OpenGL_TextView(const QString &text, const QColor &textColor) : OpenGL_TextView(text, 13, textColor) {}

OpenGL_TextView::OpenGL_TextView(const QString &text, const int &textSize, const QColor &textColor) : text(text), textSize(textSize), textColor(textColor) {}

void OpenGL_TextView::onPaintGL(QPainter * painter, GLuint *defaultFBO)
{
    // text renders as blocks when drawn to a fbo, work around this by using QImage

    auto image = createQImage();
    auto painter_ = QPainter(&image);

    painter_.setRenderHint(QPainter::Antialiasing, true);
    painter_.setRenderHint(QPainter::SmoothPixmapTransform, true);

    QFont f = painter_.font();
    f.setPixelSize(applyDpiScale(textSize));
    painter_.setFont(f);
    painter_.setPen(textColor);

    auto * l = getLayoutParams();
    Qt::AlignmentFlag alignment;
    switch (l->gravity) {
        case OpenGL_View::LayoutParams::GRAVITY_NONE:
        case OpenGL_View::LayoutParams::GRAVITY_LEFT:
            alignment = Qt::AlignmentFlag::AlignLeft;
            break;
        case OpenGL_View::LayoutParams::GRAVITY_CENTER:
            alignment = Qt::AlignmentFlag::AlignCenter;
            break;
        case OpenGL_View::LayoutParams::GRAVITY_RIGHT:
            alignment = Qt::AlignmentFlag::AlignRight;
            break;
    }

    QRect w = painter_.window();

    painter_.drawText(w, Qt::TextWordWrap | alignment, text);
    painter->drawImage(w, image);
}

const QString &OpenGL_TextView::getText() const
{
    return text;
}

void OpenGL_TextView::setText(const QString &newText)
{
    text = newText;
}

int OpenGL_TextView::getTextSize() const
{
    return textSize;
}

void OpenGL_TextView::setTextSize(int newTextSize)
{
    textSize = newTextSize;
}

const QColor &OpenGL_TextView::getTextColor() const
{
    return textColor;
}

void OpenGL_TextView::setTextColor(const QColor &newTextColor)
{
    textColor = newTextColor;
}

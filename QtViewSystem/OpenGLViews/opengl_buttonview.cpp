#include "opengl_buttonview.h"

const QString &OpenGL_ButtonView::getText() const
{
    return text;
}

void OpenGL_ButtonView::setText(const QString &newText)
{
    text = newText;
}

int OpenGL_ButtonView::getTextSize() const
{
    return textSize;
}

void OpenGL_ButtonView::setTextSize(int newTextSize)
{
    textSize = newTextSize;
}

const QColor &OpenGL_ButtonView::getTextColor() const
{
    return textColor;
}

void OpenGL_ButtonView::setTextColor(const QColor &newTextColor)
{
    textColor = newTextColor;
}

OpenGL_ButtonView::OpenGL_ButtonView() : OpenGL_ButtonView(13) {}

OpenGL_ButtonView::OpenGL_ButtonView(const QString &text) : OpenGL_ButtonView(text, 13) {}

OpenGL_ButtonView::OpenGL_ButtonView(const int &textSize) : OpenGL_ButtonView(textSize, QColorConstants::White) {}

OpenGL_ButtonView::OpenGL_ButtonView(const QColor &textColor) : OpenGL_ButtonView(13, textColor) {}

OpenGL_ButtonView::OpenGL_ButtonView(const int &textSize, const QColor &textColor) : OpenGL_ButtonView("OpenGLButtonView", textSize, textColor) {}

OpenGL_ButtonView::OpenGL_ButtonView(const QString &text, const int &textSize) : OpenGL_ButtonView(text, textSize, QColorConstants::White) {}

OpenGL_ButtonView::OpenGL_ButtonView(const QString &text, const QColor &textColor) : OpenGL_ButtonView(text, 13, textColor) {}

OpenGL_ButtonView::OpenGL_ButtonView(const QString &text, const int &textSize, const QColor &textColor) : text(text), textSize(textSize), textColor(textColor) {}

void OpenGL_ButtonView::onPaintGL(QPainter *painter, GLuint *defaultFBO)
{
    float radius = 10;
    float a = radius/2;
    QRect w = painter->window();
    QRect r = w.adjusted(a, a, -a, -a);
    if (r.isValid()) {
        image = createQImage(image);
        auto painter_ = QPainter(&image);
        painter_.setRenderHint(QPainter::Antialiasing, true);
        painter_.setRenderHint(QPainter::SmoothPixmapTransform, true);
        QPainterPath path;
        path.addRoundedRect(QRectF(w), radius, radius);
        QPen pen(Qt::green, radius);
        painter_.setPen(pen);
        painter_.fillPath(path, QColor("#404040"));
        auto c = painter_.compositionMode();
        painter_.setCompositionMode(QPainter::CompositionMode_Clear);
        painter_.drawPath(path);
        painter_.setCompositionMode(c);
        QFont f = painter_.font();
        f.setPixelSize(applyDpiScale(textSize));
        painter_.setFont(f);
        painter_.setPen(textColor);
        painter_.drawText(r, Qt::TextWordWrap | Qt::AlignmentFlag::AlignCenter, text);
        painter->drawImage(0, 0, image);
    }
}

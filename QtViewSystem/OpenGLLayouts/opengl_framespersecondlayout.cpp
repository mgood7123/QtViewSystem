#include "opengl_framespersecondlayout.h"
#include <chrono>

OpenGL_FramesPerSecondLayout::OpenGL_FramesPerSecondLayout() : OpenGL_FramesPerSecondLayout(13) {}

OpenGL_FramesPerSecondLayout::OpenGL_FramesPerSecondLayout(const int &textSize) : OpenGL_FramesPerSecondLayout(textSize, QColorConstants::White) {}

OpenGL_FramesPerSecondLayout::OpenGL_FramesPerSecondLayout(const QColor &textColor) : OpenGL_FramesPerSecondLayout(13, textColor) {}

OpenGL_FramesPerSecondLayout::OpenGL_FramesPerSecondLayout(const int &textSize, const QColor &textColor) : textSize(textSize), textColor(textColor) {
    setAlwaysDraw(true);
}

int OpenGL_FramesPerSecondLayout::getTextSize() const
{
    return textSize;
}

void OpenGL_FramesPerSecondLayout::setTextSize(int newTextSize)
{
    textSize = newTextSize;
}

const QColor &OpenGL_FramesPerSecondLayout::getTextColor() const
{
    return textColor;
}

void OpenGL_FramesPerSecondLayout::setTextColor(const QColor &newTextColor)
{
    textColor = newTextColor;
}


void OpenGL_FramesPerSecondLayout::onPaintGL(QPainter *painter, GLuint *defaultFBO)
{
    OpenGL_LayerLayout::onPaintGL(painter, defaultFBO);
    qreal targetFPS = getWindowData()->screen->refreshRate();

    QString text =
            "FPS: " + QString::number(fps) + "\n"
            + "Target FPS: " + QString::number(targetFPS) + "\n"
            + "Time: " + QString::number(differenceLastFrame * 1000) + " ms" + "\n"
            + "Target Time: " + QString::number(1000 / targetFPS) + " ms" + "\n"
            + "Elapsed: " + QString::number(elapsedLastFrame) + " seconds" + "\n"
            + "Frames: " + QString::number(frames);

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

    painter_.drawText(w, Qt::TextWordWrap | alignment | Qt::AlignmentFlag::AlignTop, text);
    painter->drawImage(w, image);
}

double OpenGL_FramesPerSecondLayout::now() {
    auto now = std::chrono::high_resolution_clock::now().time_since_epoch();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now).count();
    return static_cast<double>(ms);
}

void OpenGL_FramesPerSecondLayout::resetElapsedTime()
{
    startElapsedTime = now()/1000;
    previousElapsedTime = startElapsedTime - startElapsedTime;
    currentElapsedTime = startElapsedTime - startElapsedTime;
}

void OpenGL_FramesPerSecondLayout::elapsedTime() {
    previousElapsedTime = currentElapsedTime;
    currentElapsedTime = now()/1000 - startElapsedTime;
    elapsed = currentElapsedTime;
    difference = currentElapsedTime - previousElapsedTime;
}

void OpenGL_FramesPerSecondLayout::paintGLToFBO(int w, int h, GLuint *defaultFBO)
{
    if (!started) {
        resetElapsedTime();
        started = true;
    } else {
        currentElapsedTimeLastFrame = currentElapsedTime;
        previousElapsedTimeLastFrame = previousElapsedTime;
        differenceLastFrame = difference;
        elapsedLastFrame = elapsed;
        elapsedTime();
    }
    OpenGL_LayerLayout::paintGLToFBO(w, h, defaultFBO);
    elapsedTime();
    frames++;
    fps = frames / elapsed;
}

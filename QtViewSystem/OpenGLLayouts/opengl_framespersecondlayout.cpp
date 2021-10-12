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

    QString text;
    text += "Raw FPS: " + QString::number((int)raw_fps) + "\n";
    text += "Exponential FPS: " + QString::number((int)exponential_fps) + "\n";
    text += "Target FPS: " + QString::number(targetFPS) + "\n";
    text += "Time: " + QString::number(lastFrameTime.difference.millisecondsTotal()) + " ms\n";
    text += "Target Time: " + QString::number(1000 / targetFPS) + " ms\n";
    text += "Elapsed: " + QString::number(lastFrameTime.elapsed.secondsTotal()) + ".";
    text += QString::number(lastFrameTime.elapsed.milliseconds()).rightJustified(3, '0') + "  seconds\n";
    text += "Frames: " + QString::number(frames);

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

void OpenGL_FramesPerSecondLayout::paintGLToFBO(qreal w, qreal h, GLuint *defaultFBO)
{
    if (!frameTime.started) {
        frameTime.reset();
        fpsUpdateTime.reset();
        frames = 0;
    }
    OpenGL_LayerLayout::paintGLToFBO(w, h, defaultFBO);
    frames++;
    frameTime.elapsedTime();
    fpsUpdateTime.elapsedTime();
    if (fpsUpdateTime.elapsed.milliseconds() >= 25) {

        fpsUpdateTime.reset();

        raw_fps = (1000.0 / frameTime.difference.milliseconds());

        // calculate exponential fps to provide a
        // smoothed out the reading
        if (fpsContainer.size() == capacity) {
            fpsContainer.removeFirst();
        }
        fpsContainer.append(raw_fps);
        for (auto fps : fpsContainer) {
            N = N < avg_scale ? N+1 : N;
            exponential_fps = (exponential_fps*(N-1) + fps)/N;
        }
    }
    lastFrameTime = frameTime;
    frameTime.elapsedTime();
}

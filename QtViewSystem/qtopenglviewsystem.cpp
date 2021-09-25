#include "qtopenglviewsystem.h"

QtOpenGLViewSystem::QtOpenGLViewSystem()
{
    windowData.reset(new QTOpenGLViewSystemWindowData());
    windowData->window = this;
    windowData->screen = screen();
    windowData->dpiScale = devicePixelRatio();
}

QtOpenGLViewSystem::~QtOpenGLViewSystem()
{
    makeCurrent();
    delete contentView;
}

void QtOpenGLViewSystem::setContentView(OpenGL_View *view) {
    delete contentView;
    contentView = view;
    if (contentView != nullptr) {
        contentView->windowData = windowData.data();
        contentView->onResize(windowData->dpiScale * width(), windowData->dpiScale * height());
    }
}

void QtOpenGLViewSystem::initializeGL()
{
    QSurfaceFormat fmt;
    fmt.setDepthBufferSize(24);

    // Request OpenGL 3.3 core or OpenGL ES 3.0.
    if (QOpenGLContext::openGLModuleType() == QOpenGLContext::LibGL) {
        qDebug("Requesting 3.3 core context");
        fmt.setVersion(3, 3);
        fmt.setProfile(QSurfaceFormat::CoreProfile);
    } else {
        qDebug("Requesting 3.0 context");
        fmt.setVersion(3, 0);
    }

    QSurfaceFormat::setDefaultFormat(fmt);
    timer.setTimerType(Qt::PreciseTimer);
    timer.connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
    timer.start(8);
}

void QtOpenGLViewSystem::resizeGL(int w, int h)
{
    if (contentView != nullptr) {
        contentView->onResize(windowData->dpiScale * qreal(w), windowData->dpiScale * qreal(h));
    }
}

void QtOpenGLViewSystem::paintGL()
{
    // clear screen to black
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    if (contentView != nullptr) {
        contentView->measure();
        contentView->layout({0, 0, windowData->dpiScale * qreal(width()), windowData->dpiScale * qreal(height())});
        contentView->onPaintGL();
    }
}

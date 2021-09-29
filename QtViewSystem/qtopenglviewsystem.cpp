#include "qtopenglviewsystem.h"

QtOpenGLViewSystem::QtOpenGLViewSystem(QOpenGLWindow::UpdateBehavior updateBehavior) : QOpenGLWindow(updateBehavior)
{
    windowData.reset(new QTOpenGLViewSystemWindowData());
    windowData->window = this;
    windowData->screen = screen();
    windowData->dpiScale = devicePixelRatio();

    QSurfaceFormat fmt;
    fmt.setDepthBufferSize(24);
    fmt.setBlueBufferSize(8);
    fmt.setRedBufferSize(8);
    fmt.setGreenBufferSize(8);
    fmt.setAlphaBufferSize(8);

    // Request OpenGL 3.3 core or OpenGL ES 3.0.
    if (QOpenGLContext::openGLModuleType() == QOpenGLContext::LibGL) {
        qDebug("Requesting 3.3 core context");
        fmt.setVersion(3, 3);
        fmt.setProfile(QSurfaceFormat::CoreProfile);
    } else {
        qDebug("Requesting 3.0 context");
        fmt.setVersion(3, 0);
    }

    setFormat(fmt);
}

QtOpenGLViewSystem::~QtOpenGLViewSystem()
{
    makeCurrent();
    delete contentView;
}

void QtOpenGLViewSystem::setContentView(OpenGL_View *view) {
    OpenGL_View::LayoutParams * l = view->getLayoutParams();
    setContentView(view,  l != nullptr ? l : LAYOUT_PARAMS__MATCH_PARENT(OpenGL_View::LayoutParams));
}

void QtOpenGLViewSystem::setContentView(OpenGL_View *view, OpenGL_View::LayoutParams * params) {
    if (contentView != nullptr) {
        contentView->onRemovedFromLayout();
    }
    delete contentView;
    contentView = view;
    if (contentView != nullptr) {
        contentView->setLayoutParams(params);
        contentView->windowData = windowData.data();
        int w = windowData->applyDpiScale(width());
        int h = windowData->applyDpiScale(height());
        contentView->onResizeGL(w, h);
        contentView->onAddedToLayout();
    }
}

void QtOpenGLViewSystem::initializeGL()
{
    timer.setTimerType(Qt::PreciseTimer);
    timer.connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
    timer.start(8);
}

void QtOpenGLViewSystem::resizeGL(int w, int h)
{
    if (contentView != nullptr) {
        contentView->onResizeGL(windowData->applyDpiScale(w), windowData->applyDpiScale(h));
    }
}

void QtOpenGLViewSystem::paintGL()
{
    // enable alpha
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // clear to black
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    if (contentView != nullptr) {
        int w = windowData->applyDpiScale(width());
        int h = windowData->applyDpiScale(height());
        contentView->measure(w, h);
        contentView->onPaintGL();
    }
}

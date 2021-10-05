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

    // Request OpenGL 3.3 core or OpenGL ES 3.2
    if (QOpenGLContext::openGLModuleType() == QOpenGLContext::LibGL) {
        qDebug("Requesting 3.3 core context");
        fmt.setVersion(3, 3);
        fmt.setProfile(QSurfaceFormat::CoreProfile);
    } else {
        qDebug("Requesting 3.2 context");
        fmt.setVersion(3, 2);
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
    qDebug() << "Vendor graphic card:" << (const char *) glGetString(GL_VENDOR);
    qDebug() << "Renderer:" << (const char *) glGetString(GL_RENDERER);
    qDebug() << "Version GL:" << (const char *) glGetString(GL_VERSION);
    qDebug() << "Version GLSL:" << (const char *) glGetString(GL_SHADING_LANGUAGE_VERSION);

    timer.setTimerType(Qt::PreciseTimer);
    timer.connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
    timer.start(8);
}

void QtOpenGLViewSystem::resizeGL(int w, int h)
{
    qDebug() << "resizing system to" << windowData->applyDpiScale(w) << "," << windowData->applyDpiScale(h);
    if (contentView != nullptr) {
        contentView->onResizeGL(windowData->applyDpiScale(w), windowData->applyDpiScale(h));
    }
}

void QtOpenGLViewSystem::paintGL()
{
    // clear to black
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    if (contentView != nullptr) {
        int w = windowData->applyDpiScale(width());
        int h = windowData->applyDpiScale(height());
        contentView->buildCoordinates({0, 0, w, h});
        contentView->measure(w, h);
        contentView->paintGLToFBO(nullptr);
    }
}

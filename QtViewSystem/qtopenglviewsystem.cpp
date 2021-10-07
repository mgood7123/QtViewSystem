#include "qtopenglviewsystem.h"

QtOpenGLViewSystem::QtOpenGLViewSystem(QOpenGLWindow::UpdateBehavior updateBehavior) : QOpenGLWindow(updateBehavior)
{
    windowData = new QTOpenGLViewSystemWindowData();
    windowData->window = this;
    windowData->screen = screen();
    windowData->dpiScale = devicePixelRatio();

    QSurfaceFormat fmt;
    fmt.setAlphaBufferSize(8);
    fmt.setRedBufferSize(8);
    fmt.setGreenBufferSize(8);
    fmt.setBlueBufferSize(8);
    fmt.setDepthBufferSize(24);
    fmt.setStencilBufferSize(8);

    // Request OpenGL 4.3 core or OpenGL ES 3.2
    if (QOpenGLContext::openGLModuleType() == QOpenGLContext::LibGL) {
        qDebug("Requesting 4.3 core context");
        fmt.setVersion(4, 3);
        fmt.setProfile(QSurfaceFormat::CoreProfile);
    } else {
        qDebug("Requesting 3.2 context");
        fmt.setVersion(3, 2);
    }

    // request debug context
    fmt.setOption(QSurfaceFormat::DebugContext);

    setFormat(fmt);
}

QtOpenGLViewSystem::~QtOpenGLViewSystem()
{
    makeCurrent();
    delete contentView;
    delete logger;
    delete windowData;
}

void QtOpenGLViewSystem::setContentView(OpenGL_View *view) {
    OpenGL_View::LayoutParams * l = view->getLayoutParams();
    setContentView(view,  l != nullptr ? l : makeLayoutParams_MATCH_PARENT<OpenGL_View::LayoutParams>());
}

void QtOpenGLViewSystem::setContentView(OpenGL_View *view, OpenGL_View::LayoutParams * params) {
    if (contentView != nullptr) {
        contentView->onRemovedFromLayout();
    }
    delete contentView;
    contentView = view;
    if (contentView != nullptr) {
        contentView->setLayoutParams(params);
        contentView->setWindowData(windowData);
        int w = contentView->applyDpiScale(width());
        int h = contentView->applyDpiScale(height());
        contentView->onResizeGL(w, h);
        contentView->onAddedToLayout();
    }
}

void QtOpenGLViewSystem::handleLoggedMessage(const QOpenGLDebugMessage& debugMessage) {
    qDebug() << debugMessage;
//    auto msg = debugMessage.message().toStdString();
//    qFatal(msg.c_str());
}

void QtOpenGLViewSystem::initializeGL()
{
    qDebug() << "Vendor graphic card:" << (const char *) glGetString(GL_VENDOR);
    qDebug() << "Renderer:" << (const char *) glGetString(GL_RENDERER);
    qDebug() << "Version GL:" << (const char *) glGetString(GL_VERSION);
    qDebug() << "Version GLSL:" << (const char *) glGetString(GL_SHADING_LANGUAGE_VERSION);

    if (context()->hasExtension("GL_KHR_debug")) {
        logger = new QOpenGLDebugLogger(this);
        connect(logger, &QOpenGLDebugLogger::messageLogged, this, &QtOpenGLViewSystem::handleLoggedMessage, Qt::DirectConnection);
        if (logger->initialize()) {
            logger->startLogging(QOpenGLDebugLogger::SynchronousLogging);
        } else {
            qWarning("OpenGL context supports GL_KHR_debug extension but initialization of QOpenGLDebugLogger has failed");
        }
    } else {
        qWarning("OpenGL context does not support GL_KHR_debug extension");
    }

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
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    if (contentView != nullptr) {
        int w = windowData->applyDpiScale(width());
        int h = windowData->applyDpiScale(height());
        contentView->buildCoordinates({0, 0, w, h});
        contentView->measure(w, h);
        contentView->paintGLToFBO(nullptr);
    }
}

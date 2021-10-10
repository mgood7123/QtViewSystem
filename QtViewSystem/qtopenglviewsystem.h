#ifndef QTOPENGLVIEWSYSTEM_H
#define QTOPENGLVIEWSYSTEM_H

#include <QtDebug>
#include <QOpenGLWindow>
#include <QTimer>

#include "OpenGLViews/opengl_view.h"
#include "OpenGLViews/opengl_textview.h"
#include "OpenGLViews/opengl_colorview.h"
#include "OpenGLViews/opengl_buttonview.h"

#include "OpenGLLayouts/opengl_layout.h"
#include "OpenGLLayouts/opengl_layerlayout.h"
#include "OpenGLLayouts/opengl_linearlayout.h"
#include "OpenGLLayouts/opengl_framespersecondlayout.h"

#include "QtViewSystemManual/QtViewSystemManualView.h"

#include "qtopenglviewsystemwindowdata.h"

class QtOpenGLViewSystem : public QOpenGLWindow
{
    Q_OBJECT
    QTimer timer;
    QTOpenGLViewSystemWindowData * windowData = nullptr;
    OpenGL_View * contentView = nullptr;
    QOpenGLDebugLogger *logger = nullptr;
    void handleLoggedMessage(const QOpenGLDebugMessage& debugMessage);
public:
    QtOpenGLViewSystem(UpdateBehavior updateBehavior = NoPartialUpdate);

    ~QtOpenGLViewSystem();

    void setContentView(OpenGL_View * view);
    void setContentView(OpenGL_View * view, OpenGL_View::LayoutParams * params);

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
};

#endif // QTOPENGLVIEWSYSTEM_H

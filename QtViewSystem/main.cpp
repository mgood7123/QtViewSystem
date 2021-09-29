#include <QLoggingCategory>
#include "qtopenglviewsystem.h"
#include <QGuiApplication>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QScopedPointer<QtOpenGLViewSystem> glWindow(new QtOpenGLViewSystem());
    glWindow->show();

    OpenGL_LinearLayout * layout_B = new OpenGL_LinearLayout();
    layout_B->addChild((new OpenGL_TextView())->setText("child A")->setTextSize(13*glWindow->windowData->dpiScale));
    layout_B->addChild((new OpenGL_TextView())->setText("child B")->setTextSize(13*glWindow->windowData->dpiScale));

    OpenGL_LinearLayout * layout = new OpenGL_LinearLayout();
    layout->addChild(layout_B);
    layout->addChild((new OpenGL_TextView())->setText("child C")->setTextSize(13*glWindow->windowData->dpiScale));

    glWindow->setContentView(layout);

    return QGuiApplication::exec();
}

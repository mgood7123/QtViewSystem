#include "qtopenglviewsystem.h"
#include <QGuiApplication>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QScopedPointer<QtOpenGLViewSystem> glWindow(new QtOpenGLViewSystem());
    glWindow->show();
    glWindow->setContentView(new QtViewSystemManualView());
    return QGuiApplication::exec();
}

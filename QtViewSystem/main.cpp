#include "qtopenglviewsystem.h"
#include <QGuiApplication>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QScopedPointer<QtOpenGLViewSystem> glWindow(new QtOpenGLViewSystem());
    glWindow->show();

    auto * layer = new OpenGL_FramesPerSecondLayout();
    auto * layout_1 = new OpenGL_LinearLayout();
    layer->addChild(layout_1);
    layout_1->setVisibility(OpenGL_View::VISIBLE);
    for (int i = 0; i < 20; i++) {
//        layout_1->addChild(new OpenGL_ColorView(Qt::GlobalColor::darkBlue));
//        layout_1->addChild(new OpenGL_TextView(QString("Button ") + QString::number(i+1), 20, Qt::green));
        layout_1->addChild(new OpenGL_ButtonView(QString("Button ") + QString::number(i+1), 20, Qt::green));
    }
    glWindow->setContentView(layer);

    return QGuiApplication::exec();
}

#include "qtopenglviewsystem.h"
#include <QGuiApplication>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QScopedPointer<QtOpenGLViewSystem> glWindow(new QtOpenGLViewSystem());
    glWindow->show();
    auto * layer = new OpenGL_FramesPerSecondLayout();
    layer->setTag("layer");
    auto * layout_1 = new OpenGL_LayerLayout();
    layout_1->setTag("layout_1");
    layer->addChild(layout_1);
    for (int i = 0; i < 20; i++) {
        QString t = QString("Button ") + QString::number(i+1);
        auto * b = new OpenGL_ButtonView(t, 20, Qt::green);
        b->setTag(t);
        layout_1->addChild(b);
    }

    glWindow->setContentView(layer);

    return QGuiApplication::exec();
}

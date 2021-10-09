#include "qtopenglviewsystem.h"
#include <QGuiApplication>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QScopedPointer<QtOpenGLViewSystem> glWindow(new QtOpenGLViewSystem());
    glWindow->show();

    OpenGL_ButtonView * button_1 = new OpenGL_ButtonView("Button 1", 20, Qt::green);
    button_1->setTag("button 1");
    OpenGL_ButtonView * button_2 = new OpenGL_ButtonView("Button 2", 20, Qt::green);
    button_2->setTag("button 2");
    OpenGL_ButtonView * button_3 = new OpenGL_ButtonView("Button 3", 20, Qt::green);
    button_3->setTag("button 3");
    OpenGL_ButtonView * button_4 = new OpenGL_ButtonView("Button 4", 20, Qt::green);
    button_4->setTag("button 4");
    OpenGL_ButtonView * button_5 = new OpenGL_ButtonView("Button 5", 20, Qt::green);
    button_5->setTag("button 5");
    OpenGL_ButtonView * button_6 = new OpenGL_ButtonView("Button 6", 20, Qt::green);
    button_6->setTag("button 6");
    OpenGL_ButtonView * button_7 = new OpenGL_ButtonView("Button 7", 20, Qt::green);
    button_7->setTag("button 7");
    OpenGL_ButtonView * button_8 = new OpenGL_ButtonView("Button 8", 20, Qt::green);
    button_8->setTag("button 8");

    OpenGL_LinearLayout * layout_1 = new OpenGL_LinearLayout();
    layout_1->setTag("layout 1");
    layout_1->addChild(button_1);
    layout_1->addChild(button_2);
    OpenGL_LinearLayout * layout_2 = new OpenGL_LinearLayout();
    layout_2->setTag("layout 2");
    layout_2->addChild(button_3);
    layout_2->addChild(button_4);
    OpenGL_LinearLayout * layout_3 = new OpenGL_LinearLayout();
    layout_3->setTag("layout 3");
    layout_3->addChild(button_5);
    layout_3->addChild(button_6);
    OpenGL_LinearLayout * layout_4 = new OpenGL_LinearLayout();
    layout_4->setTag("layout 4");
    layout_4->addChild(button_7);
    layout_4->addChild(button_8);

    OpenGL_LinearLayout * layout_5 = new OpenGL_LinearLayout();
    layout_5->setTag("layout 5");
    layout_5->addChild(layout_1);
    layout_5->addChild(layout_2);
    OpenGL_LinearLayout * layout_6 = new OpenGL_LinearLayout();
    layout_6->setTag("layout 6");
    layout_6->addChild(layout_3);
    layout_6->addChild(layout_4);

    OpenGL_LinearLayout * layout_7 = new OpenGL_LinearLayout();
    layout_7->setTag("layout 7");
    layout_7->addChild(layout_5);
    layout_7->addChild(layout_6);

    glWindow->setContentView(layout_7);

    return QGuiApplication::exec();
}

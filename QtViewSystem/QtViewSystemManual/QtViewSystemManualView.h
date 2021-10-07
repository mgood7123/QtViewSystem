#ifndef QTVIEWSYSTEMMANUALVIEW_H
#define QTVIEWSYSTEMMANUALVIEW_H

#include <qtopenglviewsystem.h>

class QtViewSystemManualView : public OpenGL_LayerLayout
{
public:
    QtViewSystemManualView() {
        addChild(new OpenGL_ColorView(Qt::white));

        auto * title = new OpenGL_ButtonView("Welcome to the\nQt View System", 20, Qt::green);
        auto * titlePage = new OpenGL_LinearLayout();

        auto * ll = makeLayoutParams_MATCH_PARENT<OpenGL_LinearLayout::LinearLayoutParams>();
        ll->gravity = OpenGL_View::LayoutParams::GRAVITY_CENTER;
        ll->weight = 2;

        titlePage->addChild(title, ll);
        addChild(titlePage);
    }
};

#endif // QTVIEWSYSTEMMANUALVIEW_H

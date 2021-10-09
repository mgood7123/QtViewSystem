#include "QtViewSystemManualView.h"

QtViewSystemManualView::QtViewSystemManualView() {
    setTag("QtViewSystemManualView");
    auto c = new OpenGL_ColorView(Qt::black);
    c->setTag("OpenGL_ColorView");
    addChild(c);

    auto * titlePage = new OpenGL_LinearLayout();
    titlePage->setTag("OpenGL_LinearLayout");

//    auto * ll2 = makeLayoutParams_MATCH_PARENT<OpenGL_LinearLayout::LinearLayoutParams>();
//    ll2->gravity = OpenGL_View::LayoutParams::GRAVITY_CENTER;
//    ll2->weight = 1;

//    auto x = new OpenGL_TextView("Welcome to the\nQt View System", 20, Qt::green);
//    x->setTag("text");

//    titlePage->addChild(x, ll2);

//    auto * ll = makeLayoutParams_MATCH_PARENT<OpenGL_LinearLayout::LinearLayoutParams>();
//    ll->gravity = OpenGL_View::LayoutParams::GRAVITY_CENTER;
//    ll->weight = 1;


    auto b = new OpenGL_ButtonView("Welcome to the\nQt View System", 20, Qt::green);
    b->setTag("OpenGL_ButtonView 1");
    titlePage->addChild(b);

    b = new OpenGL_ButtonView("Welcome to the\nQt View System", 20, Qt::green);
    b->setTag("OpenGL_ButtonView 2");
    titlePage->addChild(b);

    addChild(titlePage);
}

#include <QLoggingCategory>
#include "qtopenglviewsystem.h"
#include <QGuiApplication>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QScopedPointer<QtOpenGLViewSystem> glWindow(new QtOpenGLViewSystem());
    glWindow->show();

    OpenGL_LinearLayout * layout_B = new OpenGL_LinearLayout();
    layout_B->setTag("layout B");

    auto * tvA = new OpenGL_TextView();
    tvA->setTag("child A");
    tvA->setText("child A");
    tvA->setTextSize(33*glWindow->windowData->dpiScale);
    auto a = PropertyAnimatorHelper::getFloatAnimator([tvA](auto s) {
        tvA->setTextColor(QColor(
            static_cast<uint8_t>(255 * 1), // r
            static_cast<uint8_t>(255 * 1), // b
            static_cast<uint8_t>(255 * s), // g
            static_cast<uint8_t>(255 * 1)  // a
        ));
    });
    a->setStartValue(0);
    a->setEndValue(1);
    a->setLoopCount(-1);
    a->setEasingCurve(QEasingCurve::Linear);
    a->setDuration(1000);
    tvA->addAnimation(a);
    auto * tvB = new OpenGL_TextView();
    tvB->setTag("child B");
    tvB->setText("child B");
    tvB->setTextSize(33*glWindow->windowData->dpiScale);
    auto b = PropertyAnimatorHelper::getFloatAnimator([tvB](auto s) {
        tvB->setTextColor(QColor(
            static_cast<uint8_t>(255 * s), // r
            static_cast<uint8_t>(255 * 1), // b
            static_cast<uint8_t>(255 * 1), // g
            static_cast<uint8_t>(255 * 1)  // a
        ));
    });
    b->setStartValue(0);
    b->setEndValue(1);
    b->setLoopCount(-1);
    b->setEasingCurve(QEasingCurve::Linear);
    b->setDuration(1000);
    tvB->addAnimation(b);
    auto * tvC = new OpenGL_TextView();
    tvC->setTag("child C");
    tvC->setText("child C");
    tvC->setTextSize(33*glWindow->windowData->dpiScale);
    auto c = PropertyAnimatorHelper::getFloatAnimator([tvC](auto s) {
        tvC->setTextColor(QColor(
            static_cast<uint8_t>(255 * 1), // r
            static_cast<uint8_t>(255 * s), // b
            static_cast<uint8_t>(255 * 1), // g
            static_cast<uint8_t>(255 * 1)  // a
        ));
    });
    c->setStartValue(0);
    c->setEndValue(1);
    c->setLoopCount(-1);
    c->setEasingCurve(QEasingCurve::Linear);
    c->setDuration(1000);
    tvC->addAnimation(c);

    layout_B->addChild(tvA);
    layout_B->addChild(tvB);

    OpenGL_LinearLayout * layout_A = new OpenGL_LinearLayout();
    layout_A->setTag("layout A");
    layout_A->addChild(layout_B);
    layout_A->addChild(tvC);

    glWindow->setContentView(layout_A);

    return QGuiApplication::exec();
}

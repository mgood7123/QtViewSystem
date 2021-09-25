#include "qtopenglviewsystem.h"
#include <QGuiApplication>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QScopedPointer<QtOpenGLViewSystem> glWindow(new QtOpenGLViewSystem());
    glWindow->show();

    OpenGL_LinearLayout * layer = new OpenGL_LinearLayout();
//    layer->addChild((new OpenGL_TextView())->setText("Hello!\nOpenGL By Qt")->setTextSize(36));
//    layer->addChild((new OpenGL_TextView())->setText("LargerText")->setTextSize(60));
    QEasingCurve ec = QEasingCurve::SineCurve;
    layer->addChild(
            (new OpenGL_TextView())
            ->setText("duration 1000")
            ->setTextSize(16 * glWindow->windowData->dpiScale)
            ->addAnimation([=, &glWindow](OpenGL_TextView * tv) {
                auto * anim = tv->getIntAnimator([=](auto & val) {
                    tv->setTextSize(val);
                });
                anim->setEasingCurve(ec);
                anim->setStartValue(8 * glWindow->windowData->dpiScale);
                anim->setEndValue(100 * glWindow->windowData->dpiScale);
                anim->setLoopCount(-1);
                anim->setDuration(2000);
                return anim;
            }).object
            ->setTextColor(QColorConstants::Red)
    );
    layer->addChild(
                (new OpenGL_TextView())
                ->setText("duration 1000")
                ->setTextSize(36 * glWindow->windowData->dpiScale)
                ->addAnimation([=](OpenGL_TextView * tv) {
                    auto * anim = tv->getQStringAnimator([=](auto & val) {
                        tv->setText(val);
                    });
                    anim->setEasingCurve(ec);
                    anim->setLoopCount(-1);
                    anim->setDuration(2000);
                    auto k = anim->keyValuesConstructor();
                    for (size_t count = 0; count <= 10000; ++count) {
                        qreal step = count;
                        if (count != 0) step = count / qreal(10000);
                        k.append({step, "percentage: " + QString::number(step * 100) + "%"});
                    }
                    anim->setKeyValues(k);
                    return anim;
                }).object
    );
    // 100,000 objects
//    for (int i = 0; i < 100000; i++) {
//        layer->addChild(new OpenGL_View());
//        layer->addChild((new OpenGL_TextView())->setText(QString("text ") + QString::number(i+1))->setTextColor(QColorConstants::Red));
//    }

    glWindow->setContentView(layer);

    return app.exec();
}

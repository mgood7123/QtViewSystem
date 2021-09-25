#ifndef OPENGL_VIEW_H
#define OPENGL_VIEW_H

#include <QOpenGLExtraFunctions>
#include <QDebug>
#include <qtopenglviewsystemwindowdata.h>

#include <Helpers/AnimationGroupHelper.h>
#include <Helpers/CoordinateHelper.h>
#include <Helpers/PaintHolderOpenGLHelper.h>
#include <Helpers/PropertyAnimatorHelper.h>
#include <Helpers/WindowDataHelper.h>

#include <Tools/TimeEngine.h>
#include <Tools/paintholder.h>

class OpenGL_View :
        public CoordinateHelper,
        public PaintHolderOpenGLHelper,
        public PropertyAnimatorHelper,
        public WindowDataHelper
{
    QSizeF measuredDimensions;
public:

//    ANIMATION_GROUP_HELPER_PUBLIC_BASE(OpenGL_View);

    TimeEngine timeEngine;

    QSizeF getSize();

    int getWidth();

    int getHeight();

    OpenGL_View();

    virtual ~OpenGL_View();

    void onResize(const QSizeF & size);

    class LayoutParams {
    public:
        enum GRAVITY {
            GRAVITY_NONE,
            GRAVITY_LEFT,
            GRAVITY_CENTER,
            GRAVITY_RIGHT
        };

        GRAVITY gravity;

        constexpr inline
        LayoutParams() : gravity(GRAVITY_NONE) {}

        constexpr inline
        LayoutParams(GRAVITY gravity) : gravity(gravity) {}

        template <typename T>
        T * castToType() {
            return dynamic_cast<T*>(this);
        }

        template <typename T>
        static T * castToType(LayoutParams & params) {
            return dynamic_cast<T*>(&params);
        }

        template <typename T>
        static T * castToType(LayoutParams * params) {
            return dynamic_cast<T*>(params);
        }

        virtual ~LayoutParams() = default;
    };

private:
    LayoutParams * layoutParams = nullptr;


public:
    OpenGL_View * parent = nullptr;
    float weight;

    template <typename T>
    T * castToType() {
        return dynamic_cast<T*>(this);
    }

    template <typename T>
    static T * castToType(OpenGL_View & view) {
        return dynamic_cast<T*>(&view);
    }

    template <typename T>
    static T * castToType(OpenGL_View * view) {
        return dynamic_cast<T*>(view);
    }

    LayoutParams *getLayoutParams() const;

    void setLayoutParams(LayoutParams *params);

    constexpr static QSizeF INVALID_MEASUREMENT_DIMENSION = {-1, -1};
    QRectF layoutData;
    QRectF cache_layoutData;

    void setMeasuredDimensions(const QSizeF & size);
    QSizeF getMeasuredDimensions();
    qreal getMeasuredWidth();
    qreal getMeasuredHeight();

    void measure();
    virtual void onMeasure();
    void layout(const QRectF &dimensions);
    virtual void onLayout(bool changed, const QRectF &dimensions);

    void buildCoordinates(const QRectF & relativeCoordinates);

    virtual void onResize(qreal w, qreal h);

    virtual void onAddedToLayout();
    virtual void onRemovedFromLayout();

    virtual void onPaintGL();

    virtual bool isLayout() const;

    void setGLViewport(GLint x, GLint y, GLsizei width, GLsizei height) {
        if (paintHolder.glES3Functions != nullptr) {
            paintHolder.glES3Functions->glViewport(x, y, width, height);
        }
    };

    void setGLViewport(const QRect & widthHeightCoordinates) {
        setGLViewport(widthHeightCoordinates.x(), widthHeightCoordinates.y(), widthHeightCoordinates.width(), widthHeightCoordinates.height());
    };
};

#endif // OPENGL_VIEW_H

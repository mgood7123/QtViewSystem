#ifndef OPENGL_VIEW_H
#define OPENGL_VIEW_H

#include <QBasicTimer>
#include <QDebug>
#include <QDir>
#include <QDirIterator>
#include <QFile>
#include <QImage>
#include <QImageReader>
#include <QImageWriter>
#include <QTimer>

// OpenGL
#include <QOpenGLContext>
#include <QOpenGLContextGroup>
#include <QOpenGLExtraFunctions>
#include <QOpenGLFramebufferObject>
#include <QOpenGLTexture>
#include <QOpenGLTextureBlitter>
#include <QOpenGLDebugLogger>
#include <QOpenGLDebugMessage>
#include <QOpenGLTimeMonitor>
#include <QOpenGLTimerQuery>
#include <QOpenGLTimeMonitor>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QThread>


#include <qtopenglviewsystemwindowdata.h>

#include <QParallelAnimationGroup>
#include <QSequentialAnimationGroup>

#include <Helpers/CoordinateHelper.h>
#include <Helpers/PaintHolderOpenGLHelper.h>
#include <Helpers/PropertyAnimatorHelper.h>
#include <Helpers/WindowDataHelper.h>

#include <Tools/PixelToNDC.h>
#include <Tools/TimeEngine.h>
#include <Tools/paintholder.h>
#include <Tools/lambdathread.h>
#include <QPainterPath>



// SUPER IMPORTANT: INVALIDATE YOUR VIEWS!!!!!!!!!
//
// android gets around the problem of excessive overdraw via view invalidation
//   - it will ONLY draw view's that have been explicitly invalidated
//     to avoid redrawing the same view hundreds of times even if nothing
//     at all has changed



class OpenGL_View :
        public CoordinateHelper,
        public PaintHolderOpenGLHelper,
        public WindowDataHelper
{
public:
    enum VISIBILITY {
        VISIBLE, INVISIBLE, GONE
    };
private:
    QSize measuredDimensions {-1, -1};
    static constexpr const char * NO_TAG = "<INTERNAL_VIEW__NO_TAG>";
    const char * tag = NO_TAG;
    bool canDraw = false;
    VISIBILITY visibility = VISIBLE;
public:

    void setTag(const char * name);
    const char * getTag();

protected:
QParallelAnimationGroup animationGroup;
public:

    QSequentialAnimationGroup * getSequentialAnimationGroup();

    QParallelAnimationGroup * getParallelAnimationGroup();

    void addAnimation(QAbstractAnimation * animation);

    void removeAnimation(QAbstractAnimation * animation);

    void startAnimation(QAbstractAnimation::DeletionPolicy policy = QAbstractAnimation::DeletionPolicy::KeepWhenStopped);

    void pauseAnimation();

    void stopAnimation();

    TimeEngine timeEngine;

    QSize getWindowSize();

    int getWindowWidth();

    int getWindowHeight();

    OpenGL_View();

    virtual ~OpenGL_View();

    enum MeasureSpec {
        MATCH_PARENT = -1,
        WRAP_CONTENT = -2
    };

    class LayoutParams {
    public:
        enum GRAVITY {
            GRAVITY_NONE,
            GRAVITY_LEFT,
            GRAVITY_CENTER,
            GRAVITY_RIGHT
        };

        int width = MATCH_PARENT;
        int height = MATCH_PARENT;
        GRAVITY gravity = GRAVITY_NONE;

        LayoutParams(int width, int height);

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

protected:
    virtual void onPaintGL(QPainter * painter, GLuint *defaultFBO);

public:
    PixelToNDC pixelToNDC;
    OpenGL_View * parent = nullptr;
    float weight = 0;

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

    constexpr static QSize INVALID_MEASUREMENT_DIMENSION = {-1, -1};
    QRect layoutData;
    QRect cache_layoutData;

    void setMeasuredDimensions(int width, int height);
    void setMeasuredDimensions(const QSize & size);
    QSize getMeasuredDimensions();
    int getMeasuredWidth();
    int getMeasuredHeight();

    void measure(int width, int height);
    virtual void onMeasure(int width, int height);

    void buildCoordinates(const QRect & relativeCoordinates);

    void onResizeGL(QSize window_size);
    virtual void onResizeGL(int window_w, int window_h);

    virtual void onAddedToLayout();
    virtual void onRemovedFromLayout();

    virtual bool isLayout() const;

    void setGLViewport(GLint x, GLint y, GLsizei width, GLsizei height);

    void setGLViewport(const QRect & widthHeightCoordinates);

    template<typename T> bool isPowerOf2(T const x) { return x && !( x & (x - 1) ); };

    void check_glError(QOpenGLExtraFunctions * gl, const char * tag = nullptr);

    void check_glError(GLenum error, const char * tag = nullptr);

    void check_glCheckFramebufferStatus(QOpenGLExtraFunctions * gl, GLenum target, const char * tag = nullptr);

    void resizeFBO(int w, int h);

    QImage createQImage();

    QImage createQImage(uint pixel);

    QImage createQImage(const QColor &color);

    QImage createQImage(Qt::GlobalColor color);

    QImage createQImage(const QImage & comparisonImage);

    QImage createQImage(const QImage & comparisonImage, uint pixel);

    QImage createQImage(const QImage & comparisonImage, const QColor &color);

    QImage createQImage(const QImage & comparisonImage, Qt::GlobalColor color);

    bool generated = false;

    GLuint quadVAO, quadVBO;
    GLuint fbo = 0, fbo_color_texture = 0, fbo_depth_renderbuffer = 0;
    QOpenGLShaderProgram program;

    void bindFBO();

    void drawFBO(int w, int h, GLuint * defaultFBO);

    void destroyFBO();

    virtual void paintGLToFBO(int w, int h, GLuint * defaultFBO);
    VISIBILITY getVisibility() const;
    void setVisibility(VISIBILITY newVisibility);
};

template<typename T>
T * makeLayoutParams_MATCH_PARENT() {
    return new T(OpenGL_View::MATCH_PARENT, OpenGL_View::MATCH_PARENT);
}

template<typename T>
T * makeLayoutParams_WRAP_CONTENT() {
    return new T(OpenGL_View::WRAP_CONTENT, OpenGL_View::WRAP_CONTENT);
}

template<typename T>
T * makeLayoutParams_MATCH_PARENT_WRAP_CONTENT() {
    return new T(OpenGL_View::MATCH_PARENT, OpenGL_View::WRAP_CONTENT);
}

template<typename T>
T * makeLayoutParams_WRAP_CONTENT_MATCH_PARENT() {
    return new T(OpenGL_View::WRAP_CONTENT, OpenGL_View::MATCH_PARENT);
}

#endif // OPENGL_VIEW_H

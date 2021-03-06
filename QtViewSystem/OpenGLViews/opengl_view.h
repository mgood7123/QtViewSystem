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
#include <QPainter>
#include <QPainterPath>
#include <QPicture>
#include <QBitmap>

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
#include <Tools/chronotimer.h>


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
    bool in_loop = false;
public:
    enum VISIBILITY {
        VISIBLE, INVISIBLE, GONE
    };

    // TODO: consider using custom class with explicit math_parent and wrap_content flags
    static qreal MATCH_PARENT;
    static qreal WRAP_CONTENT;

    class LayoutParams {
    public:
        enum GRAVITY {
            GRAVITY_NONE,
            GRAVITY_LEFT,
            GRAVITY_CENTER,
            GRAVITY_RIGHT
        };

        qreal width = MATCH_PARENT;
        qreal height = MATCH_PARENT;
        GRAVITY gravity = GRAVITY_NONE;

        LayoutParams(qreal width, qreal height);

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
    QSizeF measuredDimensions {0, 0};
    bool calledSetMeasuredDimensions = false;
    static constexpr const char * NO_TAG = "<INTERNAL_VIEW__NO_TAG>";
    QString tag = NO_TAG;
    bool canDraw = false;
    VISIBILITY visibility = VISIBLE;
    bool invalidated = true;
    bool fboGenerated = false;
    GLuint quadVAO = 0, quadVBO = 0;
    GLuint fbo = 0, fbo_color_texture = 0, fbo_depth_renderbuffer = 0;
    int fboWidth = 0, fboHeight = 0;
    static QOpenGLShaderProgram program;
    LayoutParams * layoutParams = nullptr;
    bool alwaysDraw = false;
    bool erased_texture = false;
public:

    void setAlwaysDraw(bool enabled);

    bool getAlwaysDraw() const;

    void invalidate();

    void setTag(const QString & name);
    QString getTag() const;

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

    virtual ~OpenGL_View();

protected:
    virtual void onPaintGL(QPainter * painter, GLuint *defaultFBO);

public:
    PixelToNDC pixelToNDC;
    OpenGL_View * parent = nullptr;
    qreal weight = 0;

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

    void setMeasuredDimensions(qreal width, qreal height);
    void setMeasuredDimensions(const QSizeF & size);
    QSizeF getMeasuredDimensions();
    qreal getMeasuredWidth();
    qreal getMeasuredHeight();

    void measure(qreal width, qreal height);
    virtual void onMeasure(qreal width, qreal height);

    void buildCoordinates(const QRectF & relativeCoordinates);

    void onResizeGL(QSize window_size);
    void onResizeGL(QSizeF window_size);
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

    inline static
    constexpr int qrealToPixel(qreal pixel) {
        // round to pixel + 1 so we can downscale
        return pixel + 0.5;
    };

    QImage createQImage();

    QImage createQImage(uint pixel);

    QImage createQImage(const QColor &color);

    QImage createQImage(Qt::GlobalColor color);

    QImage createQImage(const QImage & comparisonImage);

    QImage createQImage(const QImage & comparisonImage, uint pixel);

    QImage createQImage(const QImage & comparisonImage, const QColor &color);

    QImage createQImage(const QImage & comparisonImage, Qt::GlobalColor color);

    void bindFBO();

    void drawFBO(qreal w, qreal h, GLuint * defaultFBO);

    void destroyFBO();

    virtual void paintGLToFBO(qreal w, qreal h, GLuint * defaultFBO);
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

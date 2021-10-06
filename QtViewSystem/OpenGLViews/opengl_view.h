#ifndef OPENGL_VIEW_H
#define OPENGL_VIEW_H

#include <QDebug>
#include <QDir>
#include <QDirIterator>
#include <QFile>

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
#include <QPainterPath>

class OpenGL_View :
        public CoordinateHelper,
        public PaintHolderOpenGLHelper,
        public WindowDataHelper
{
    QSize measuredDimensions;
    static constexpr const char * NO_TAG = "<INTERNAL_VIEW__NO_TAG>";
    const char * tag = NO_TAG;
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

    virtual void onPaintGL(QPainter * painter, GLuint * defaultFBO);

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

    void createFBO(int w, int h);

    void createFBO(int w, int h, GLenum internalTextureFormat);

    void createFBO(int w, int h, QOpenGLFramebufferObject::Attachment attachment);

    GLuint fbo, fbo_color_texture, fbo_depth_renderbuffer;
    GLuint fboMSAA, fboMSAA_depth_renderbuffer;
    QOpenGLTexture fboMSAA_color_texture = QOpenGLTexture(QOpenGLTexture::Target2DMultisample);
    bool fboMSAA_color_texture_configured = false;

    void createFBO(int w, int h, GLenum internalTextureFormat, QOpenGLFramebufferObject::Attachment attachment);

    void bindFBO();

    void drawFBO(GLuint * defaultFBO);

    void destroyFBO();

    void paintGLToFBO(GLuint * defaultFBO);
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

#include "opengl_view.h"

QSize OpenGL_View::getWindowSize() { return paintHolder.getSize(); }

int OpenGL_View::getWindowWidth() { return getWindowSize().width(); }

int OpenGL_View::getWindowHeight() { return getWindowSize().height(); }

OpenGL_View::OpenGL_View() {}

OpenGL_View::~OpenGL_View() {
    delete layoutParams;
    destroyFBO();
}

OpenGL_View::VISIBILITY OpenGL_View::getVisibility() const
{
    return visibility;
}

void OpenGL_View::setVisibility(VISIBILITY newVisibility)
{
    visibility = newVisibility;
}

void OpenGL_View::setTag(const char *name) {
    tag = name;
}

const char * OpenGL_View::getTag() {
    return tag;
}

QSequentialAnimationGroup *OpenGL_View::getSequentialAnimationGroup() {
    return new QSequentialAnimationGroup();
}

QParallelAnimationGroup *OpenGL_View::getParallelAnimationGroup() {
    return new QParallelAnimationGroup();
}

void OpenGL_View::addAnimation(QAbstractAnimation *animation) {
    animationGroup.addAnimation(animation);
}

void OpenGL_View::removeAnimation(QAbstractAnimation *animation) {
    animationGroup.removeAnimation(animation);
}

void OpenGL_View::startAnimation(QAbstractAnimation::DeletionPolicy policy) {
    animationGroup.start(policy);
}

void OpenGL_View::pauseAnimation() {
    animationGroup.pause();
}

void OpenGL_View::stopAnimation() {
    animationGroup.stop();
}

OpenGL_View::LayoutParams *OpenGL_View::getLayoutParams() const {
    return layoutParams;
}

void OpenGL_View::setLayoutParams(LayoutParams *params) {
    // important optimization:
    // if params are self, then
    //   do not delete layoutParams
    //     it will invalidate/corrupt the passed params
    //     since it points to layoutParams, resulting in use-after-free
    //
    //   avoid this useless assignment:
    //     LayoutParams * params = layoutParams;
    //     layoutParams = params;
    if (params != layoutParams) {
        delete layoutParams;
        layoutParams = params;
    }
}

void OpenGL_View::measure(int width, int height)
{
    if (visibility == GONE) return;
    measuredDimensions = INVALID_MEASUREMENT_DIMENSION;
    onMeasure(width, height);
    if (measuredDimensions == INVALID_MEASUREMENT_DIMENSION) {
        qFatal("invalid measurement, did you forget to call `setMeasuredDimensions(const QSize &);` ?");
    }
}

void OpenGL_View::setMeasuredDimensions(int width, int height)
{
    setMeasuredDimensions({width, height});
}

void OpenGL_View::setMeasuredDimensions(const QSize &size)
{
    canDraw = !size.isEmpty();
    measuredDimensions = size;
}

QSize OpenGL_View::getMeasuredDimensions()
{
    return measuredDimensions;
}

int OpenGL_View::getMeasuredWidth()
{
    return measuredDimensions.width();
}

int OpenGL_View::getMeasuredHeight()
{
    return measuredDimensions.height();
}

void OpenGL_View::onMeasure(int width, int height)
{
    LayoutParams * params = getLayoutParams();
    QSize measuredDimensions = QSize{params->width, params->height};
    if (params->width == MATCH_PARENT) {
        measuredDimensions.setWidth(width);
    } else if (params->width == WRAP_CONTENT) {
        measuredDimensions.setWidth(0);
    }
    if (params->height == MATCH_PARENT) {
        measuredDimensions.setHeight(height);
    } else if (params->height == WRAP_CONTENT) {
        measuredDimensions.setHeight(0);
    }
    setMeasuredDimensions(measuredDimensions);
}

void OpenGL_View::onResizeGL(QSize window_size) {
    onResizeGL(window_size.width(), window_size.height());
}

void OpenGL_View::onResizeGL(int window_w, int window_h) {
    bool resizeOccured = paintHolder.resize(window_w, window_h);
    canDraw = paintHolder.paintDeviceOpenGL != nullptr;
    if (canDraw) {
        // dont resize fbo if the size did not change
        if (resizeOccured) {
            resizeFBO(window_w, window_h);
        }
    } else {
        if (generated) destroyFBO();
    }
}

void OpenGL_View::onAddedToLayout()
{
    startAnimation();
}

void OpenGL_View::onRemovedFromLayout()
{
    stopAnimation();
}

void OpenGL_View::onPaintGL(QPainter * painter, GLuint *defaultFBO) {}

bool OpenGL_View::isLayout() const {
    return false;
}

void OpenGL_View::setGLViewport(GLint x, GLint y, GLsizei width, GLsizei height) {
    if (paintHolder.glES3Functions != nullptr) {
        paintHolder.glES3Functions->glViewport(x, y, width, height);
    }
}

void OpenGL_View::setGLViewport(const QRect &widthHeightCoordinates) {
    setGLViewport(widthHeightCoordinates.x(), widthHeightCoordinates.y(), widthHeightCoordinates.width(), widthHeightCoordinates.height());
}

void OpenGL_View::check_glError(QOpenGLExtraFunctions *gl, const char * tag) {
    check_glError(gl->glGetError(), tag);
}

void OpenGL_View::check_glError(GLenum error, const char * tag) {
    switch(error) {
    case GL_NO_ERROR: break;
    default: {
#define QTVSGLE(name) case name: { \
    QString msg = "ERROR: "; \
    if (tag != nullptr) { \
        msg += "(TAG: "; \
        msg += tag; \
        msg += ") "; \
    } \
    msg += #name; \
    std::string stdmsg = msg.toStdString(); \
    qFatal("%s", stdmsg.c_str()); \
}
        switch(error) {
            QTVSGLE(GL_INVALID_ENUM);
            QTVSGLE(GL_INVALID_FRAMEBUFFER_OPERATION);
            QTVSGLE(GL_INVALID_OPERATION);
            QTVSGLE(GL_INVALID_VALUE);
            QTVSGLE(GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT);
            QTVSGLE(GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT);
            QTVSGLE(GL_FRAMEBUFFER_UNSUPPORTED);
#ifndef Q_OS_ANDROID
            QTVSGLE(GL_INVALID_INDEX);
            QTVSGLE(GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE);
            QTVSGLE(GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS);
            QTVSGLE(GL_FRAMEBUFFER_UNDEFINED);
#endif
            QTVSGLE(GL_OUT_OF_MEMORY);
            default: {
                QString msg = "ERROR: ";
                if (tag != nullptr) {
                    msg += "(TAG: ";
                    msg += tag;
                    msg += ") ";
                }
                msg += QString::number(error);
                std::string stdmsg = msg.toStdString();
                qFatal("%s", stdmsg.c_str());
            }
        }
#undef QTVSGLE
    }
    }
}

void OpenGL_View::check_glCheckFramebufferStatus(QOpenGLExtraFunctions *gl, GLenum target, const char * tag) {
    GLenum s = gl->glCheckFramebufferStatus(target);
    switch(s) {
    case GL_FRAMEBUFFER_COMPLETE:
        break;
    default: {
        QString msg = "ERROR: ";
        if (tag != nullptr) {
            msg += "(TAG: ";
            msg += tag;
            msg += ") ";
        }
        switch(s) {
        case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT: {
            msg += "GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT (returned if any of the framebuffer attachment points are framebuffer incomplete)";
            std::string stdmsg = msg.toStdString(); \
            qFatal("%s", stdmsg.c_str()); \
        }
        case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT: {
            msg += "GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT (returned if the framebuffer does not have at least one image attached to it)";
            std::string stdmsg = msg.toStdString(); \
            qFatal("%s", stdmsg.c_str()); \
        }
        case GL_FRAMEBUFFER_UNSUPPORTED: {
            msg += "GL_FRAMEBUFFER_UNSUPPORTED (returned if depth and stencil attachments, if present, are not the same renderbuffer, or if the combination of internal formats of the attached images violates an implementation-dependent set of restrictions)";
            std::string stdmsg = msg.toStdString(); \
            qFatal("%s", stdmsg.c_str()); \
        }
#ifndef Q_OS_ANDROID
        case GL_FRAMEBUFFER_UNDEFINED: {
            msg += "GL_FRAMEBUFFER_UNDEFINED (returned if target is the default framebuffer, but the default framebuffer does not exist)";
            std::string stdmsg = msg.toStdString(); \
            qFatal("%s", stdmsg.c_str()); \
        }
        case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE: {
            msg += "GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE (returned if the value of GL_RENDERBUFFER_SAMPLES is not the same for all attached renderbuffers or, if the attached images are a mix of renderbuffers and textures, the value of GL_RENDERBUFFER_SAMPLES is not zero)";
            std::string stdmsg = msg.toStdString(); \
            qFatal("%s", stdmsg.c_str()); \
        }
        case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS: {
            msg += "GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS (returned if any framebuffer attachment is layered, and any populated attachment is not layered, or if all populated color attachments are not from textures of the same target)";
            std::string stdmsg = msg.toStdString(); \
            qFatal("%s", stdmsg.c_str()); \
        }
#endif
        default: {
            check_glError(gl, tag);
        }
        }
    }
    }
}

void OpenGL_View::resizeFBO(int w, int h) {
    auto gl = getOpenGLExtraFunctions();
    if (gl == nullptr) return;
    if (w == 0 || h == 0) {
        destroyFBO();
        return;
    }

    if (generated) {
        // texture buffers must be destroyed and then recreated in order to be resized
        // ONLY if they are immutable storage (glTexStorage*)
        // use glTexImage instead to avoid recreating
        gl->glDeleteTextures(1, &fbo_color_texture);
        gl->glGenTextures(1, &fbo_color_texture);
    } else {
        gl->glGenTextures(1, &fbo_color_texture);
        gl->glGenRenderbuffers(1, &fbo_depth_renderbuffer);
        gl->glGenFramebuffers(1, &fbo);
        generated = true;
    }

    // color
    gl->glBindTexture(GL_TEXTURE_2D, fbo_color_texture);
    gl->glTexStorage2D(GL_TEXTURE_2D, 1,
#ifdef Q_OS_ANDROID
        GL_RGBA8_OES
#else
        GL_RGBA8
#endif
    , w, h);

    // depth
    gl->glBindRenderbuffer(GL_RENDERBUFFER, fbo_depth_renderbuffer);
    gl->glRenderbufferStorage(GL_RENDERBUFFER,
#ifdef Q_OS_ANDROID
      GL_DEPTH24_STENCIL8_OES
#else
      GL_DEPTH24_STENCIL8
#endif
    , w, h);

    // fbo
    gl->glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    gl->glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fbo_color_texture, 0);
    gl->glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, fbo_depth_renderbuffer);
    check_glCheckFramebufferStatus(gl, GL_FRAMEBUFFER, "FBO");

    // clear the FBO to transparent
    gl->glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    gl->glClearColor(0, 0, 0, 0);
    gl->glClear(GL_COLOR_BUFFER_BIT);
}

QImage OpenGL_View::createQImage() {
    return createQImage(Qt::transparent);
}

QImage OpenGL_View::createQImage(uint pixel) {
    QImage image(paintHolder.getSize(), QImage::Format_RGBA8888);
    // initialize QImage to transparent
    image.fill(pixel);
    return image;
}

QImage OpenGL_View::createQImage(const QColor &color) {
    QImage image(paintHolder.getSize(), QImage::Format_RGBA8888);
    // initialize QImage to transparent
    image.fill(color);
    return image;
}

QImage OpenGL_View::createQImage(Qt::GlobalColor color) {
    QImage image(paintHolder.getSize(), QImage::Format_RGBA8888);
    // initialize QImage to transparent
    image.fill(color);
    return image;
}

QPixmap OpenGL_View::createQPixmap() {
    return createQPixmap(Qt::transparent);
}

QPixmap OpenGL_View::createQPixmap(uint pixel) {
    QPixmap image(paintHolder.getSize());
    // initialize QImage to transparent
    image.fill(pixel);
    return image;
}

QPixmap OpenGL_View::createQPixmap(const QColor &color) {
    QPixmap image(paintHolder.getSize());
    // initialize QImage to transparent
    image.fill(color);
    return image;
}

QPixmap OpenGL_View::createQPixmap(Qt::GlobalColor color) {
    QPixmap image(paintHolder.getSize());
    // initialize QImage to transparent
    image.fill(color);
    return image;
}

void OpenGL_View::bindFBO() {
    auto gl = getOpenGLExtraFunctions();
    gl->glBindFramebuffer(GL_FRAMEBUFFER, fbo);
}

void OpenGL_View::drawFBO(int w, int h, GLuint *defaultFBO) {
    auto gl = getOpenGLExtraFunctions();

    if (defaultFBO != nullptr) {
        gl->glBindFramebuffer(GL_FRAMEBUFFER, *defaultFBO);
    } else {
        QOpenGLFramebufferObject::bindDefault();
    }

    if (!program.isLinked()) {
        auto vf = QFile(":/OpenGL Shaders/default_framebuffer_renderer.vsh");
        vf.open(QFile::OpenModeFlag::ReadOnly);

        auto ff = QFile(":/OpenGL Shaders/default_framebuffer_renderer.fsh");
        ff.open(QFile::OpenModeFlag::ReadOnly);

        auto v = vf.readAll();
        auto f = ff.readAll();

        vf.close();
        ff.close();

        // Any number representing a version of the language a compiler does not support
        // will cause an error to be generated.

        if (getOpenGLContext()->isOpenGLES()) {
            // android supports OpenGL ES 3.0 since android 4.3 (kitkat)

            // android supports OpenGL ES 3.1 since android 5.0 (lollipop)
            //  New functionality in OpenGL ES 3.1 includes:
            //   Compute shaders
            //   Independent vertex and fragment shaders
            //   Indirect draw commands

            // android supports OpenGL ES 3.2 since android 6.0 (marshmellow), possibly 7.0 (naugat)

            // OpenGL ES 3.0 (#version 300 es)
            // OpenGL ES 3.1 (#version 310 es)
            // OpenGL ES 3.2 (#version 320 es)

            v.prepend(QByteArrayLiteral("#version 300 es\n"));
            f.prepend(QByteArrayLiteral("#version 300 es\n"));
        } else {
            // OpenGL 3.3 (GLSL #version 330)
            v.prepend(QByteArrayLiteral("#version 330\n"));
            f.prepend(QByteArrayLiteral("#version 330\n"));
        }
        if (!program.addShaderFromSourceCode(QOpenGLShader::Vertex, v)) {
            qFatal("OPENGL SHADER VERTEX SHADER COMPILATION FAILED");
        }
        if (!program.addShaderFromSourceCode(QOpenGLShader::Fragment, f)) {
            qFatal("OPENGL SHADER FRAGMENT SHADER COMPILATION FAILED");
        }
        if (!program.link()) {
            qFatal("OPENGL SHADER LINK FAILED");
        }
    }

    program.bind();

    int draw_x = relativeCoordinates.topLeftX;
    int draw_y = relativeCoordinates.topLeftY;
    int draw_w = relativeCoordinates.bottomRightX;
    int draw_h = relativeCoordinates.bottomRightY;

    gl->glEnable(GL_SCISSOR_TEST);
    gl->glScissor(0, 0, w, h);
    gl->glViewport(0, 0, w, h);
    pixelToNDC.resize(w, h);

    auto topLeft = pixelToNDC.toNDC<int, float>(draw_x, draw_y, false);
    auto topRight = pixelToNDC.toNDC<int, float>(draw_w, draw_y, false);
    auto bottomRight = pixelToNDC.toNDC<int, float>(draw_x, draw_h, false);
    auto bottomLeft = pixelToNDC.toNDC<int, float>(draw_w, draw_h, false);

    float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
     // positions                  // texCoords
     topLeft.x,     topLeft.y,     0, 1,
     bottomRight.x, bottomRight.y, 0, 0,
     bottomLeft.x,  bottomLeft.y,  1, 0,

     topLeft.x,     topLeft.y,     0, 1,
     bottomLeft.x,  bottomLeft.y,  1, 0,
     topRight.x,    topRight.y,    1, 1
   };

    // screen quad VAO
    gl->glGenVertexArrays(1, &quadVAO);
    gl->glGenBuffers(1, &quadVBO);
    gl->glBindVertexArray(quadVAO);
    gl->glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    gl->glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    gl->glEnableVertexAttribArray(0);
    gl->glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    gl->glEnableVertexAttribArray(1);
    gl->glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

    gl->glBindVertexArray(quadVAO);
    gl->glDisable(GL_DEPTH_TEST);
    gl->glBindTexture(GL_TEXTURE_2D, fbo_color_texture);
    gl->glDrawArrays(GL_TRIANGLES, 0, 6);
    gl->glDeleteVertexArrays(1, &quadVAO);
    gl->glDeleteBuffers(1, &quadVBO);

    gl->glDisable(GL_SCISSOR_TEST);

    program.release();
}

void OpenGL_View::destroyFBO() {
    auto gl = getOpenGLExtraFunctions();
    if (gl == nullptr) return;

    if (generated) {
        gl->glDeleteTextures(1, &fbo_color_texture);
        gl->glDeleteRenderbuffers(1, &fbo_depth_renderbuffer);
        gl->glDeleteFramebuffers(1, &fbo);

        generated = false;
    }
}

void OpenGL_View::paintGLToFBO(int w, int h, GLuint *defaultFBO) {
    switch (visibility) {
        case OpenGL_View::VISIBLE:
            break;
        case OpenGL_View::INVISIBLE:
        case OpenGL_View::GONE:
            return;
    }
    if (!canDraw) {
        if (generated) destroyFBO();
        paintHolder.deallocate();
        return;
    }
    onResizeGL(measuredDimensions);
    if (!canDraw) {
        return;
    }
    if (paintHolder.paintDeviceOpenGL == nullptr) {
        canDraw = false;
        return;
    }
    bindFBO();
    auto * gl = getOpenGLExtraFunctions();

    // clear FBO to transparent
    gl->glClearColor(0, 0, 0, 0);
    gl->glClear(GL_COLOR_BUFFER_BIT);

    gl->glEnable(GL_DEPTH_TEST);
    gl->glEnable(GL_BLEND);
    gl->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    auto * painterGL = paintHolder.beginGL();
    onPaintGL(painterGL, &fbo);
    painterGL->end();

    gl->glEnable(GL_DEPTH_TEST);
    gl->glEnable(GL_BLEND);
    gl->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    drawFBO(w, h, defaultFBO);
}

void OpenGL_View::buildCoordinates(const QRect &relativeCoordinates) {
    this->relativeCoordinates = relativeCoordinates;
    if (parent == nullptr) {
        absoluteCoordinates = this->relativeCoordinates;
    } else {
        int atlx = parent->absoluteCoordinates.topLeftX + this->relativeCoordinates.topLeftX;
        int atly = parent->absoluteCoordinates.topLeftY + this->relativeCoordinates.topLeftY;
        int abrx = parent->absoluteCoordinates.topLeftX + this->relativeCoordinates.bottomRightX;
        int abry = parent->absoluteCoordinates.topLeftY + this->relativeCoordinates.bottomRightY;
        absoluteCoordinates = CoordinateInfo(atlx, atly, abrx, abry);
    }
}

OpenGL_View::LayoutParams::LayoutParams(int width, int height) : width(width), height(height) {}

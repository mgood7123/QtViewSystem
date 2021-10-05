#include "opengl_view.h"

QSize OpenGL_View::getWindowSize() { return paintHolder.getSize(); }

int OpenGL_View::getWindowWidth() { return getWindowSize().width(); }

int OpenGL_View::getWindowHeight() { return getWindowSize().height(); }

OpenGL_View::OpenGL_View() {}

OpenGL_View::~OpenGL_View() {
    delete layoutParams;
    destroyFBO();
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
    measuredDimensions = INVALID_MEASUREMENT_DIMENSION;
    onMeasure(width, height);
    if (measuredDimensions == INVALID_MEASUREMENT_DIMENSION) {
        qFatal("invalid measurement, did you forget to call setMeasuredDimensions(const QSize &); ?");
    }
}

void OpenGL_View::setMeasuredDimensions(int width, int height)
{
    setMeasuredDimensions({width, height});
}

void OpenGL_View::setMeasuredDimensions(const QSize &size)
{
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
    paintHolder.resize(window_w, window_h);
    createFBO(window_w, window_h);
}

void OpenGL_View::onAddedToLayout()
{
    startAnimation();
}

void OpenGL_View::onRemovedFromLayout()
{
    stopAnimation();
}

void OpenGL_View::onPaintGL(QPainter * painter, QOpenGLFramebufferObject * defaultFBO) {}

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

void OpenGL_View::createFBO(int w, int h) {
    createFBO(w, h, GL_RGBA, QOpenGLFramebufferObject::Attachment::CombinedDepthStencil);
}

void OpenGL_View::createFBO(int w, int h, GLenum internalTextureFormat) {
    createFBO(w, h, internalTextureFormat, QOpenGLFramebufferObject::Attachment::CombinedDepthStencil);
}

void OpenGL_View::createFBO(int w, int h, QOpenGLFramebufferObject::Attachment attachment) {
    createFBO(w, h, GL_RGBA, attachment);
}

void OpenGL_View::createFBO(int w, int h, GLenum internalTextureFormat, QOpenGLFramebufferObject::Attachment attachment) {
    destroyFBO();

    auto gl = getOpenGLExtraFunctions();
    if (gl == nullptr) return;

    // create framebuffer

    QOpenGLFramebufferObjectFormat muliSampleFormat;
    muliSampleFormat.setAttachment(attachment);
    muliSampleFormat.setSamples(8);
    // a renderbuffer will be created
    fboAA = new QOpenGLFramebufferObject(w, h, muliSampleFormat);

    fboAA->bind();
    if(gl->glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        throw new std::runtime_error("ERROR::FRAMEBUFFER:: Framebuffer is not complete!");
    }

    // clear the current FBO to transparent
    gl->glClearColor(0, 0, 0, 0);
    gl->glClear(GL_COLOR_BUFFER_BIT);

    QOpenGLFramebufferObjectFormat fbo_format;
    fbo_format.setAttachment(attachment);
    fbo_format.setInternalTextureFormat(internalTextureFormat);

    fbo = new QOpenGLFramebufferObject(w, h, fbo_format);

    fbo->bind();

    // configure the texture
    gl->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    gl->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    if(gl->glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        throw new std::runtime_error("ERROR::FRAMEBUFFER:: Framebuffer is not complete!");
    }
    // dont clear as we copy fboAA directly to this
    fbo->release();
    fboAA->bind();
}

void OpenGL_View::bindFBO() {
    fboAA->bind();
}

void OpenGL_View::drawFBO(QOpenGLFramebufferObject *defaultFBO) {
    fboAA->release();
    if (defaultFBO != nullptr) {
        defaultFBO->bind();
    } else {
        QOpenGLFramebufferObject::bindDefault();
    }

    int w = getWindowWidth();
    int h = getWindowHeight();

    // blit fboAA to fbo
    QOpenGLFramebufferObject::blitFramebuffer(fbo, fboAA, GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT, GL_NEAREST);

    auto gl = getOpenGLExtraFunctions();
    QOpenGLShaderProgram program;

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
        throw new std::runtime_error("OPENGL SHADER VERTEX SHADER COMPILATION FAILED");
    }
    if (!program.addShaderFromSourceCode(QOpenGLShader::Fragment, f)) {
        throw new std::runtime_error("OPENGL SHADER FRAGMENT SHADER COMPILATION FAILED");
    }
    if (!program.link()) {
        throw new std::runtime_error("OPENGL SHADER LINK FAILED");
    }
    program.bind();

    int offset_x = absoluteCoordinates.rectTopLeft.x();
    int offset_y = absoluteCoordinates.rectTopLeft.y();
    int clip_w = absoluteCoordinates.rectBottomRight.x();
    int clip_h = absoluteCoordinates.rectBottomRight.y();

    gl->glEnable(GL_SCISSOR_BIT);
    gl->glScissor(offset_x, offset_y, clip_w, clip_h);

    // draw full screen
    int offset_w = w + offset_x;
    int offset_h = h + offset_y;

    pixelToNDC.resize(w, h);

    auto topLeft = pixelToNDC.toNDC<int, float>(offset_x, offset_y, false);
    auto topRight = pixelToNDC.toNDC<int, float>(offset_w, offset_y, false);
    auto bottomRight = pixelToNDC.toNDC<int, float>(offset_x, offset_h, false);
    auto bottomLeft = pixelToNDC.toNDC<int, float>(offset_w, offset_h, false);

    float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
     // positions   // texCoords
     topLeft.x,     topLeft.y,     0.0f, 1.0f,
     bottomRight.x, bottomRight.y, 0.0f, 0.0f,
     bottomLeft.x,  bottomLeft.y,  1.0f, 0.0f,

     topLeft.x,     topLeft.y,     0.0f, 1.0f,
     bottomLeft.x,  bottomLeft.y,  1.0f, 0.0f,
     topRight.x,    topRight.y,    1.0f, 1.0f
   };

    // screen quad VAO
    unsigned int quadVAO, quadVBO;
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
    gl->glBindTexture(GL_TEXTURE_2D, fbo->texture());
    gl->glDrawArrays(GL_TRIANGLES, 0, 6);

    gl->glDeleteVertexArrays(1, &quadVAO);
    gl->glDeleteBuffers(1, &quadVBO);

    program.release();
}

void OpenGL_View::destroyFBO() {
    if (fboAA != nullptr) fboAA->release();
    delete fboAA;
    fboAA = nullptr;
    if (fbo != nullptr) fbo->release();
    delete fbo;
    fbo = nullptr;
}

void OpenGL_View::paintGLToFBO(QOpenGLFramebufferObject *defaultFBO) {
    bindFBO();
    // draw to framebuffer
    auto * gl = getOpenGLExtraFunctions();
    // clear the current FBO to transparent
    gl->glClearColor(0, 0, 0, 0);
    gl->glClear(GL_COLOR_BUFFER_BIT);

    gl->glEnable(GL_DEPTH_TEST);
    gl->glEnable(GL_BLEND);
    gl->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    auto * painter = paintHolder.begin();
    onPaintGL(painter, fboAA);
    painter->end();

    gl->glEnable(GL_DEPTH_TEST);
    gl->glEnable(GL_BLEND);
    gl->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    drawFBO(defaultFBO);
}

void OpenGL_View::buildCoordinates(const QRect &relativeCoordinates) {
    this->relativeCoordinates = relativeCoordinates;
    if (parent == nullptr) {
        absoluteCoordinates = this->relativeCoordinates;
    } else {
        absoluteCoordinates = CoordinateInfo(relativeCoordinates.translated(parent->absoluteCoordinates.rectTopLeft));
    }
}

OpenGL_View::LayoutParams::LayoutParams(int width, int height) : width(width), height(height) {}

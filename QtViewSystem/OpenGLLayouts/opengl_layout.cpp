#include "opengl_layout.h"

bool OpenGL_Layout::isLayout() const {
    return true;
}

OpenGL_Layout::~OpenGL_Layout() {
    removeAllChildren();
}

void OpenGL_Layout::addChild(OpenGL_View *view) {
    LayoutParams * l = view->getLayoutParams();
    addChild(view,  l != nullptr ? l : new LayoutParams(MATCH_PARENT, MATCH_PARENT));
}

void OpenGL_Layout::addChild(OpenGL_View *view, LayoutParams * params) {
    if (view == nullptr) {
        qFatal("cannot add a nullptr view");
    }
    if (params == nullptr) {
        qFatal("cannot assign a nullptr LayoutParams");
    }
    view->setLayoutParams(params);
    view->windowData = windowData;
    view->parent = this;
    view->onResizeGL(getWindowSize());
    children.append(view);
    view->onAddedToLayout();
}

void OpenGL_Layout::detachChild(OpenGL_View *view) {
    if (view == nullptr) {
        qFatal("cannot detach a nullptr view");
    }
    qsizetype count = children.size();
    for (qsizetype i = 0; i < count; i++) {
        OpenGL_View * child = children[i];
        if (child == view) {
            view->onRemovedFromLayout();
            children.remove(i);
            break;
        }
    }
    view->windowData = nullptr;
}

void OpenGL_Layout::removeChild(OpenGL_View *view) {
    if (view == nullptr) {
        qFatal("cannot remove a nullptr view");
    }
    qsizetype count = children.size();
    for (qsizetype i = 0; i < count; i++) {
        OpenGL_View * child = children[i];
        if (child == view) {
            view->onRemovedFromLayout();
            delete view;
            children.remove(i);
            break;
        }
        break;
    }
}

void OpenGL_Layout::removeAllChildren() {
    qsizetype count = children.size();
    for (qsizetype i = 0; i < count; i++) {
        OpenGL_View * view = children[i];
        view->onRemovedFromLayout();
        delete view;
        children.remove(i);
        break;
    }
}

void OpenGL_Layout::onResizeGL(int window_w, int window_h)
{
    paintHolder.resize(window_w, window_h);
    for (OpenGL_View * view: children) {
        view->onResizeGL(window_w, window_h);
    }
}


void OpenGL_Layout::onPaintGL()
{
    if (true) {
        for (int i = 0; i < 2; i++) {
            // obtain window width and height, these are automatically scaled by the window dpi
            int w = getWindowWidth();
            int h = getWindowHeight();

            auto gl = getOpenGLExtraFunctions();

            // create framebuffer
            GLuint framebuffer;
            gl->glGenFramebuffers(1, &framebuffer);

            // generate texture
            GLuint texture;
            gl->glGenTextures(1, &texture);

            // bind texture and configure
            gl->glBindTexture(GL_TEXTURE_2D, texture);
            gl->glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
            gl->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
            gl->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            // generate renderbuffer
            unsigned int renderbuffer;
            gl->glGenRenderbuffers(1, &renderbuffer);

            // bind renderbuffer and configure it
            gl->glBindRenderbuffer(GL_RENDERBUFFER, renderbuffer);
            gl->glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8_OES, w, h);

            // bind framebuffer and attach texture and renderbuffer
            gl->glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
            gl->glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);
            gl->glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_LAYOUT_DEPTH_STENCIL_ATTACHMENT_EXT, GL_RENDERBUFFER, renderbuffer);

            if(gl->glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
                throw new std::runtime_error("ERROR::FRAMEBUFFER:: Framebuffer is not complete!");
            }

            // draw to framebuffer
            gl->glEnable(GL_DEPTH_TEST);
            gl->glEnable(GL_BLEND);
            gl->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            // first pass
            switch(i) {
                case 0:
                    // draw solid red
                    gl->glClearColor(1, 0, 0, 1);
                    gl->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                    break;
                case 1:
                    // draw transparent blue
                    gl->glClearColor(0, 0, 1, 0.25);
                    gl->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                    break;
            }

//            int vertexLocation = program.attributeLocation("vertex");
//            int colorLocation = program.uniformLocation("color");

//            static GLfloat const triangleVertices[] = {
//                60.0f,  10.0f,  0.0f,
//                110.0f, 110.0f, 0.0f,
//                10.0f,  110.0f, 0.0f
//            };

//            QColor color(0, 255, 0, 255);

//            program.enableAttributeArray(vertexLocation);
//            program.setAttributeArray(vertexLocation, triangleVertices, 3);
//            program.setUniformValue(colorLocation, color);

//            glDrawArrays(GL_TRIANGLES, 0, 3);

//            program.disableAttributeArray(vertexLocation);

            // second pass
            gl->glBindFramebuffer(GL_FRAMEBUFFER, 0); // back to default
            gl->glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
            gl->glClear(GL_COLOR_BUFFER_BIT);

            QOpenGLShaderProgram program;

            auto vf = QFile(":/OpenGL Shaders/default_framebuffer_renderer.vsh");
            vf.open(QFile::OpenModeFlag::ReadOnly);

            auto ff = QFile(":/OpenGL Shaders/default_framebuffer_renderer.fsh");
            ff.open(QFile::OpenModeFlag::ReadOnly);

            auto v = vf.readAll();
            auto f = ff.readAll();

            vf.close();
            ff.close();

            if (QOpenGLContext::currentContext()->isOpenGLES()) {
                v.prepend(QByteArrayLiteral("#version 300 es\n"));
                f.prepend(QByteArrayLiteral("#version 300 es\n"));
            } else {
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

            float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
                // positions   // texCoords
                -1.0f,  1.0f,  0.0f, 1.0f,
                -1.0f, -1.0f,  0.0f, 0.0f,
                 1.0f, -1.0f,  1.0f, 0.0f,

                -1.0f,  1.0f,  0.0f, 1.0f,
                 1.0f, -1.0f,  1.0f, 0.0f,
                 1.0f,  1.0f,  1.0f, 1.0f
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
            gl->glBindTexture(GL_TEXTURE_2D, texture);
            gl->glDrawArrays(GL_TRIANGLES, 0, 6);

            gl->glDeleteVertexArrays(1, &quadVAO);
            gl->glDeleteBuffers(1, &quadVBO);

            program.release();

            // bind default texture and renderbuffer
            gl->glBindTexture(GL_TEXTURE_2D, 0);
            gl->glBindRenderbuffer(GL_RENDERBUFFER, 0);

            // clean up
            gl->glDeleteFramebuffers(1, &framebuffer);
            gl->glDeleteTextures(1, &texture);
            gl->glDeleteRenderbuffers(1, &renderbuffer);
        }
    } else {
        // this works but draws directly to default FBO
        for (OpenGL_View * view: children) {
            view->paintHolder.painter->save();
            view->paintHolder.painter->translate(view->relativeCoordinates.rectTopLeft);
            view->paintHolder.painter->setClipping(true);
            view->paintHolder.painter->setClipRect(view->relativeCoordinates.clipRect);
            view->onPaintGL();
            view->paintHolder.painter->restore();
        }
    }
}

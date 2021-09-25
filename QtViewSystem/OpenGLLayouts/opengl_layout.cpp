#include "opengl_layout.h"

bool OpenGL_Layout::isLayout() const {
    return true;
}

OpenGL_Layout::~OpenGL_Layout() {
    removeAllChildren();
}

void OpenGL_Layout::addChild(OpenGL_View *view) {
    LayoutParams * l = view->getLayoutParams();
    addChild(view,  l != nullptr ? l : new LayoutParams());
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
    view->onResize(getSize());
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

void OpenGL_Layout::onResize(qreal w, qreal h)
{
    paintHolder.resize(w, h);
    for (OpenGL_View * view: children) {
        view->onResize(w, h);
    }
}

void OpenGL_Layout::onPaintGL()
{
    for (OpenGL_View * view: children) {
        view->paintHolder.painter->save();
        view->paintHolder.painter->translate(view->relativeCoordinates.rectTopLeft);
        view->paintHolder.painter->setClipping(true);
        view->paintHolder.painter->setClipRect(view->relativeCoordinates.clipRect);
        view->onPaintGL();
        view->paintHolder.painter->restore();
    }
}

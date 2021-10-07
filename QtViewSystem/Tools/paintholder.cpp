#include "paintholder.h"

QPainter *PaintHolder::beginGL() {
    if (painterGL == nullptr) return nullptr;
    painterGL->begin(paintDeviceOpenGL);
    return painterGL;
}

void PaintHolder::resize(const QSize &size) {
    allocate(size);
}

void PaintHolder::resize(const int &width, const int &height) {
    allocate(width, height);
}

void PaintHolder::deallocate()
{
    delete painterGL;
    painterGL = nullptr;
    glES3Functions = nullptr;
    glES2Functions = nullptr;
    glContext = nullptr;
    delete paintDeviceOpenGL;
    paintDeviceOpenGL = nullptr;
}

void PaintHolder::allocate(const QSize &size)
{
    if (this->size != size) {
        allocate(size.width(), size.height());
    }
}

void PaintHolder::allocate(const int &width, const int &height)
{
    QSize s = {width, height};
    if (size != s) {
        size = s;
        deallocate();
        paintDeviceOpenGL = new QOpenGLPaintDevice(width, height);
        painterGL = new QPainter();
        glContext = paintDeviceOpenGL->context();
        glES2Functions = glContext->functions();
        glES3Functions = glContext->extraFunctions();
    }
}

QSize PaintHolder::getSize() {
    return size;
}

PaintHolder::PaintHolder(const QSize &size) {
    allocate(size);
}

PaintHolder::PaintHolder(const int &width, const int &height) {
    allocate(width, height);
}

PaintHolder::PaintHolder(const PaintHolder &other) {
    resize(other.size);
}

PaintHolder &PaintHolder::operator=(const PaintHolder &other) {
    resize(other.size);
    return *this;
}

PaintHolder::PaintHolder(PaintHolder &&other) {
    size = other.size;
    other.size = {0, 0};

    glES3Functions = other.glES3Functions;
    other.glES3Functions = nullptr;

    glES2Functions = other.glES2Functions;
    other.glES2Functions = nullptr;

    glContext = other.glContext;
    other.glContext = nullptr;

    paintDeviceOpenGL = other.paintDeviceOpenGL;
    other.paintDeviceOpenGL = nullptr;
}

PaintHolder &PaintHolder::operator=(PaintHolder &&other) {
    deallocate();

    size = other.size;
    other.size = {0, 0};

    glES3Functions = other.glES3Functions;
    other.glES3Functions = nullptr;

    glES2Functions = other.glES2Functions;
    other.glES2Functions = nullptr;

    glContext = other.glContext;
    other.glContext = nullptr;

    return *this;
}

PaintHolder::~PaintHolder() {
    deallocate();
}

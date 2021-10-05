#include "paintholder.h"

QPainter *PaintHolder::begin() {
    if (painter == nullptr) return nullptr;
    painter->begin(paintDevice);
    return painter;
}

void PaintHolder::resize(const QSize &size) {
    allocate(size);
}

void PaintHolder::resize(const int &width, const int &height) {
    allocate(width, height);
}

void PaintHolder::deallocate()
{
    delete painter;
    painter = nullptr;
    glES3Functions = nullptr;
    glES2Functions = nullptr;
    glContext = nullptr;
    delete paintDevice;
    paintDevice = nullptr;
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
        paintDevice = new QOpenGLPaintDevice(width, height);
        painter = new QPainter();
        glContext = paintDevice->context();
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
    deallocate();
    size = other.size;
    other.size = {0, 0};

    paintDevice = other.paintDevice;
    other.paintDevice = nullptr;

    painter = other.painter;
    other.painter = nullptr;
}

PaintHolder &PaintHolder::operator=(PaintHolder &&other) {
    deallocate();
    size = other.size;
    other.size = {0, 0};

    paintDevice = other.paintDevice;
    other.paintDevice = nullptr;

    painter = other.painter;
    other.painter = nullptr;
    return *this;
}

PaintHolder::~PaintHolder() {
    deallocate();
}

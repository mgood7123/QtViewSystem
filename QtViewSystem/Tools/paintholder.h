#ifndef PAINTHOLDER_H
#define PAINTHOLDER_H

#include <QOpenGLPaintDevice>
#include <QPainter>

class PaintHolder {
    QSize size = {-1, -1};

public:

    QOpenGLPaintDevice * paintDevice = nullptr;
    QPainter * painter = nullptr;

    QOpenGLContext * glContext = nullptr;
    QOpenGLFunctions * glES2Functions = nullptr;
    QOpenGLExtraFunctions* glES3Functions = nullptr;

    QPainter * begin();

    void resize(const QSize & size);

    void resize(const int & width, const int & height);

    void deallocate();

    void allocate(const QSize & size);

    void allocate(const int & width, const int & height);

    QSize getSize();

    PaintHolder() = default;

    PaintHolder(const QSize & size);

    PaintHolder(const int & width, const int & height);

    PaintHolder(const PaintHolder & other);

    PaintHolder&operator=(const PaintHolder & other);

    PaintHolder(PaintHolder && other);

    PaintHolder&operator=(PaintHolder && other);

    ~PaintHolder();
};

#endif // PAINTHOLDER_H

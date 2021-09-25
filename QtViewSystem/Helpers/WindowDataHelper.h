#ifndef WINDOWDATAHELPER_H
#define WINDOWDATAHELPER_H

#include <qtopenglviewsystemwindowdata.h>

class WindowDataHelper {
    public:
    // points to read-only data managed by QTOpenGLViewSystem
    const QTOpenGLViewSystemWindowData * windowData = nullptr;
};

#endif // WINDOWDATAHELPER_H

QT       += opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Helpers/CoordinateHelper.cpp \
    Helpers/PaintHolderOpenGLHelper.cpp \
    Helpers/PropertyAnimatorHelper.cpp \
    OpenGLLayouts/opengl_layerlayout.cpp \
    OpenGLLayouts/opengl_layout.cpp \
    OpenGLLayouts/opengl_linearlayout.cpp \
    OpenGLViews/opengl_colorview.cpp \
    OpenGLViews/opengl_textview.cpp \
    OpenGLViews/opengl_view.cpp \
    Tools/PixelToNDC.cpp \
    Tools/TimeEngine.cpp \
    Tools/paintholder.cpp \
    main.cpp \
    qtopenglviewsystem.cpp

HEADERS += \
    Helpers/CoordinateHelper.h \
    Helpers/PaintHolderOpenGLHelper.h \
    Helpers/PropertyAnimatorHelper.h \
    Helpers/WindowDataHelper.h \
    OpenGLLayouts/opengl_layerlayout.h \
    OpenGLLayouts/opengl_layout.h \
    OpenGLLayouts/opengl_linearlayout.h \
    OpenGLViews/opengl_colorview.h \
    OpenGLViews/opengl_textview.h \
    OpenGLViews/opengl_view.h \
    Tools/PixelToNDC.h \
    Tools/TimeEngine.h \
    Tools/TypeSafeKeyValuePropertyAnimators.h \
    Tools/TypeSafePropertyAnimators.h \
    Tools/paintholder.h \
    qtopenglviewsystem.h \
    qtopenglviewsystemwindowdata.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    OpenGL Shaders/default_framebuffer_renderer.fsh \
    OpenGL Shaders/default_framebuffer_renderer.vsh \
    OpenGL Shaders/example_fragment_desktop.frag \
    OpenGL Shaders/example_fragment_es2.fsh \
    OpenGL Shaders/example_vertex_desktop.vsh \
    OpenGL Shaders/example_vertex_es2.vsh \
    OpenGL Shaders/s.frag \
    android/AndroidManifest.xml \
    android/build.gradle \
    android/gradle.properties \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew.bat \
    android/res/values/libs.xml

contains(ANDROID_TARGET_ARCH,arm64-v8a) {
    ANDROID_PACKAGE_SOURCE_DIR = \
        $$PWD/android
}

RESOURCES += \
    Resource_Files.qrc

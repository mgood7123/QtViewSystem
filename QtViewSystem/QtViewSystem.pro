QT += opengl

CONFIG += c++11
CONFIG += warn_on
QMAKE_CXXFLAGS += "-Wreturn-type"
QMAKE_CFLAGS += "-Wreturn-type"

# sanitizer slows down execution
#CONFIG += sanitizer
#CONFIG += sanitize_address
# clang++: error: invalid argument '-fsanitize=address' not allowed with '-fsanitize=memory'
#CONFIG += sanitize_memory
# clang++: error: invalid argument '-fsanitize=address' not allowed with '-fsanitize=thread'
#CONFIG += sanitize_thread
#CONFIG += sanitize_undefined

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Helpers/CoordinateHelper.cpp \
    Helpers/PaintHolderOpenGLHelper.cpp \
    Helpers/PropertyAnimatorHelper.cpp \
    Helpers/WindowDataHelper.cpp \
    OpenGLLayouts/opengl_framespersecondlayout.cpp \
    OpenGLLayouts/opengl_layerlayout.cpp \
    OpenGLLayouts/opengl_layout.cpp \
    OpenGLLayouts/opengl_linearlayout.cpp \
    OpenGLViews/opengl_buttonview.cpp \
    OpenGLViews/opengl_colorview.cpp \
    OpenGLViews/opengl_textview.cpp \
    OpenGLViews/opengl_view.cpp \
    QtViewSystemManual/QtViewSystemManualView.cpp \
    Tools/PixelToNDC.cpp \
    Tools/TimeEngine.cpp \
    Tools/chronotimer.cpp \
    Tools/lambdathread.cpp \
    Tools/paintholder.cpp \
    main.cpp \
    qtopenglviewsystem.cpp \
    qtopenglviewsystemwindowdata.cpp

HEADERS += \
    Helpers/CoordinateHelper.h \
    Helpers/PaintHolderOpenGLHelper.h \
    Helpers/PropertyAnimatorHelper.h \
    Helpers/WindowDataHelper.h \
    OpenGLLayouts/opengl_framespersecondlayout.h \
    OpenGLLayouts/opengl_layerlayout.h \
    OpenGLLayouts/opengl_layout.h \
    OpenGLLayouts/opengl_linearlayout.h \
    OpenGLViews/opengl_buttonview.h \
    OpenGLViews/opengl_colorview.h \
    OpenGLViews/opengl_textview.h \
    OpenGLViews/opengl_view.h \
    QtViewSystemManual/QtViewSystemManualView.h \
    Tools/PixelToNDC.h \
    Tools/TimeEngine.h \
    Tools/TypeSafeKeyValuePropertyAnimators.h \
    Tools/TypeSafePropertyAnimators.h \
    Tools/chronotimer.h \
    Tools/lambdathread.h \
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
    android/AndroidManifest.xml \
    android/build.gradle \
    android/gradle.properties \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew.bat \
    android/res/values/libs.xml

RESOURCES += \
    Resource_Files.qrc

contains(ANDROID_TARGET_ARCH,arm64-v8a) {
    ANDROID_PACKAGE_SOURCE_DIR = \
        $$PWD/android
}

contains(ANDROID_TARGET_ARCH,armeabi-v7a) {
    ANDROID_PACKAGE_SOURCE_DIR = \
        $$PWD/android
}

contains(ANDROID_TARGET_ARCH,x86_64) {
    ANDROID_PACKAGE_SOURCE_DIR = \
        $$PWD/android
}

contains(ANDROID_TARGET_ARCH,x86) {
    ANDROID_PACKAGE_SOURCE_DIR = \
        $$PWD/android
}

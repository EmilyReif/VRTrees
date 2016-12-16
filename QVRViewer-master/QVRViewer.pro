#-------------------------------------------------
#
# Project created by QtCreator 2016-09-28T00:52:41
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

TARGET = QVRViewer
TEMPLATE = app


SOURCES += src/main.cpp\
    src/mainwindow.cpp \
    src/vrview.cpp \
    src/databinding.cpp \
    src/forestmaker.cpp \
    src/glwidget.cpp \
    src/settings.cpp \
    cs123_lib/errorchecker.cpp \
    cs123_lib/resourceloader.cpp \
    lsystem/lsystemgenerator.cpp \
    shapes/Cap.cpp \
    shapes/Cone.cpp \
    shapes/Cylinder.cpp \
    shapes/lsystemtree.cpp \
    shapes/ModeratelyComplexShape.cpp \
    shapes/OpenGLShape.cpp \
    shapes/Sphere.cpp \
    shapes/Square.cpp \
    shapes/Torus.cpp \
    src/glib/datatype/FBO.cpp \
    src/glib/datatype/IBO.cpp \
    src/glib/datatype/VAO.cpp \
    src/glib/datatype/VBO.cpp \
    src/glib/datatype/VBOAttribMarker.cpp \
    src/glib/textures/DepthBuffer.cpp \
    src/glib/textures/RenderBuffer.cpp \
    src/glib/textures/Texture.cpp \
    src/glib/textures/Texture2D.cpp \
    src/glib/textures/TextureParameters.cpp \
    src/glib/textures/TextureParametersBuilder.cpp \
    src/glib/GLDebug.cpp \
    extern/glew/src/glew.c

HEADERS  += src/mainwindow.h \
    src/modelformats.h \
    src/vrview.h \
    src/databinding.h \
    src/forestmaker.h \
    src/glwidget.h \
    src/settings.h \
    cs123_lib/errorchecker.h \
    cs123_lib/resourceloader.h \
    cs123_lib/sphere.h \
    lsystem/lsystemgenerator.h \
    shapes/Cap.h \
    shapes/Cone.h \
    shapes/Cylinder.h \
    shapes/lsystemtree.h \
    shapes/ModeratelyComplexShape.h \
    shapes/OpenGLShape.h \
    shapes/Sphere.h \
    shapes/Square.h \
    shapes/Torus.h \
    src/glib/datatype/FBO.h \
    src/glib/datatype/IBO.h \
    src/glib/datatype/VAO.h \
    src/glib/datatype/VBO.h \
    src/glib/datatype/VBOAttribMarker.h \
    src/glib/shaders/ShaderAttribLocations.h \
    src/glib/textures/DepthBuffer.h \
    src/glib/textures/RenderBuffer.h \
    src/glib/textures/Texture.h \
    src/glib/textures/Texture2D.h \
    src/glib/textures/TextureParameters.h \
    src/glib/textures/TextureParametersBuilder.h \
    src/glib/GLDebug.h

FORMS    += src/mainwindow.ui

DEFINES +=  _CRT_NO_VA_START_VALIDATION
DEFINES += GLEW_STATIC
DEFINES += GLM_SWIZZLE GLM_FORCE_RADIANS



# from http://stackoverflow.com/a/10058744
# Copies the given files to the destination directory
defineTest(copyToDestdir) {
    files = $$1

    for(FILE, files) {
        CONFIG( debug, debug|release ) {
            DDIR = $${OUT_PWD}/debug
        } else {
            DDIR = $${OUT_PWD}/release
        }

        # Replace slashes in paths with backslashes for Windows
        win32:FILE ~= s,/,\\,g
        win32:DDIR ~= s,/,\\,g

        QMAKE_POST_LINK += $$QMAKE_COPY $$quote($$FILE) $$quote($$DDIR) $$escape_expand(\\n\\t)
    }

    export(QMAKE_POST_LINK)
}


win32 {
    RC_FILE = win32.rc

    contains(QT_ARCH, i386) {
message("32 bit build")
        LIBS += -L$$PWD/extern/openvr/lib/win32/ \
                -lopenvr_api -lopengl32 -lglu32
        copyToDestdir($${PWD}/extern/openvr/bin/win32/openvr_api.dll)
    } else {
message("64 bit build")
        LIBS += -L$$PWD/extern/openvr/lib/win64/ \
                -lopenvr_api -lopengl32 -lglu32
        copyToDestdir($${PWD}/extern/openvr/bin/win64/openvr_api.dll)
    }
}

INCLUDEPATH += $$PWD/extern/openvr/headers $$PWD/extern/glew/include
INCLUDEPATH += glm
DEPENDPATH += glm


# from http://stackoverflow.com/a/25193580
isEmpty(TARGET_EXT) {
    win32 {
        TARGET_CUSTOM_EXT = .exe
    }
    macx {
        TARGET_CUSTOM_EXT = .app
    }
} else {
    TARGET_CUSTOM_EXT = $${TARGET_EXT}
}

win32 {
    DEPLOY_COMMAND = windeployqt
}
macx {
    DEPLOY_COMMAND = macdeployqt
}

CONFIG( debug, debug|release ) {
    # debug
    DEPLOY_TARGET = $$shell_quote($$shell_path($${OUT_PWD}/debug/$${TARGET}$${TARGET_CUSTOM_EXT}))
} else {
    # release
    DEPLOY_TARGET = $$shell_quote($$shell_path($${OUT_PWD}/release/$${TARGET}$${TARGET_CUSTOM_EXT}))
}

QMAKE_POST_LINK += $${DEPLOY_COMMAND} $${DEPLOY_TARGET} $$escape_expand(\\n\\t)

RESOURCES += \
    resources.qrc \
    shaders/shaders.qrc

DISTFILES += \
    win32.rc \
    viewer.ico \
    shaders/deferredShadingFirst.frag \
    shaders/deferredShadingSecond.frag \
    shaders/deferredShadingFirst.vert \
    shaders/quad.vert


QT += core gui opengl xml widgets
TARGET = proj_anim_squelette
TEMPLATE = app

# include path for QGLViewer & glm
INCLUDEPATH += ..

DESTDIR =$$_PRO_FILE_PWD_/../bin/

# define path for shaders
QMAKE_CXXFLAGS += -DSHADERPATH=$$_PRO_FILE_PWD_

# System dependent options

# Linux & macOS/X
unix {
QMAKE_CXXFLAGS += -std=c++11
QMAKE_LFLAGS +=  -Wl,-rpath,$$_PRO_FILE_PWD_/../bin
LIBS += -L$$_PRO_FILE_PWD_/../bin -lOGLRender -lQGLViewer33
}

# Windows (64b)
win32 {
QMAKE_CXXFLAGS += -D_USE_MATH_DEFINES
QMAKE_CXXFLAGS_WARN_ON += -wd4267 -wd4244 -wd4305
LIBS += -L$$_PRO_FILE_PWD_/../bin -lOGLRender -lQGLViewer33 -lopengl32
}

SOURCES += main.cpp primitives.cpp \
    squelette.cpp

HEADERS  += matrices.h primitives.h \
    squelette.h

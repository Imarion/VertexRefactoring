QT += gui core

CONFIG += c++11

TARGET = VertexRefactoring
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    Triangle.cpp \
    vertexcol.cpp \
    vertextex.cpp \
    vertexfactory.cpp \
    ivertexfactory.cpp \
    vertex.cpp

HEADERS += \
    Triangle.h \
    vertexcol.h \
    vertextex.h \
    vertexfactory.h \
    ivertexfactory.h \
    vertex.h

OTHER_FILES += \
    vshader_col.txt \
    fshader_col.txt \
    fshader_norm.txt \
    vshader_norm.txt

RESOURCES += \
    shaders.qrc

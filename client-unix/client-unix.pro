TEMPLATE = app
CONFIG += console
CONFIG -= qt

QMAKE_CXXFLAGS += -std=gnu++0x

HEADERS += \
    unixapplication.h \
    xviewport.h

SOURCES += \
    main.cpp \
    unixapplication.cpp \
    xviewport.cpp

INCLUDEPATH += ../renderer/base \
                ../renderer/comm \
                ../renderer/math \
                ../renderer/rend \
                ../renderer/third-party/include/ \
                ../renderer

LIBS += ../../bin/renderer/librenderer.a
LIBS += ../../renderer/third-party/lib/libyaml-cpp.a

LIBS += -lX11 -lboost_system -lboost_filesystem

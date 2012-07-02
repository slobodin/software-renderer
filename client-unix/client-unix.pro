TEMPLATE = app
CONFIG += console
CONFIG -= qt

QMAKE_CXXFLAGS += -std=gnu++0x

DEFINES += LINUX_VERSION

INCLUDEPATH += ../renderer/base \
                ../renderer/comm \
                ../renderer/math \
                ../renderer/rend \
                ../renderer/third-party/include/ \
                ../renderer

LIBS += ../../bin/renderer/librenderer.a
LIBS += ../../renderer/third-party/lib/libyaml-cpp.a

LIBS += -lX11 -lboost_system -lboost_filesystem

PRE_TARGETDEPS += ../../bin/renderer/librenderer.a

HEADERS += \
    application.h

SOURCES += \
    main.cpp \
    application.cpp

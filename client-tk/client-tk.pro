TEMPLATE = app
CONFIG += console
CONFIG -= qt

QMAKE_CXXFLAGS += -std=gnu++0x

DEFINES += TK_VERSION

INCLUDEPATH += ../renderer/base \
                ../renderer/comm \
                ../renderer/math \
                ../renderer/rend \
                ../renderer/third-party/include/ \
                ../renderer

LIBS += ../../bin/renderer/librenderer.a
LIBS += ../../renderer/third-party/lib/libyaml-cpp.a

LIBS += -lboost_system -lboost_filesystem -lboost_regex

PRE_TARGETDEPS += ../../bin/renderer/librenderer.a

SOURCES += \
    main.cpp \
    tkapplication.cpp

HEADERS += \
    tkapplication.h

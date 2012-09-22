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
                ../renderer \
                /usr/include/tcl8.5

LIBS += ../../bin/renderer/librenderer.a

unix:LIBS += ../../renderer/third-party/lib/libyaml-cpp.a
unix:LIBS += -lboost_system -lboost_filesystem -lboost_regex -ltcl8.5 -ltk8.5

win32:LIBS += ./third-party/lib/mingw/libyaml-cpp.a
win32:LIBS += $(BOOST_ROOT)/stage/lib/libboost_filesystem-mgw46-mt-1_49.a
win32:LIBS += $(BOOST_ROOT)/stage/lib/libboost_system-mgw46-mt-1_49.a

PRE_TARGETDEPS += ../../bin/renderer/librenderer.a

SOURCES += \
    main.cpp \
    tkapplication.cpp

HEADERS += \
    tkapplication.h

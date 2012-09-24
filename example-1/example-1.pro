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
                $(BOOST_ROOT) \
                /usr/include/tcl8.5

unix:LIBS += ../../bin/renderer/librenderer.a

CONFIG(debug, debug|release) {
win32:LIBS += ../../bin/renderer/debug/librenderer.a        # if debug
}
CONFIG(release, debug|release) {
win32:LIBS += ../../bin/renderer/release/librenderer.a        # if release
}

win32:INCLUDEPATH += $(TCL_ROOT)/include

unix:LIBS += ../../renderer/third-party/lib/libyaml-cpp.a
unix:LIBS += -lboost_system -lboost_filesystem -ltcl8.5 -ltk8.5

win32:LIBS += ../../renderer/third-party/lib/mingw/libyaml-cpp.a
win32:LIBS += $(BOOST_ROOT)/stage/lib/libboost_filesystem-mgw46-mt-1_49.a
win32:LIBS += $(BOOST_ROOT)/stage/lib/libboost_system-mgw46-mt-1_49.a
win32:LIBS += $(TCL_ROOT)/lib/tcl85.lib
win32:LIBS += $(TCL_ROOT)/lib/tk85.lib

unix:PRE_TARGETDEPS += ../../bin/renderer/librenderer.a
CONFIG(debug, debug|release) {
win32:PRE_TARGETDEPS += ../../bin/renderer/debug/librenderer.a
}
CONFIG(release, debug|release) {
win32:PRE_TARGETDEPS += ../../bin/renderer/release/librenderer.a
}

SOURCES += \
    main.cpp \
    example1application.cpp

HEADERS += \
    example1application.h

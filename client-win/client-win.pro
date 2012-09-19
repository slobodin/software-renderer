TEMPLATE = app
CONFIG += console
CONFIG -= qt

QMAKE_CXXFLAGS += -std=gnu++0x

INCLUDEPATH += ../renderer/base \
                ../renderer/comm \
                ../renderer/math \
                ../renderer/rend \
                ../renderer/third-party/include/ \
                ../renderer \
                $(BOOST_ROOT)

HEADERS += \
    windowsviewport.h \
    windowsapplication.h

SOURCES += \
    windowsviewport.cpp \
    windowsapplication.cpp \
    main.cpp

LIBS += ../../bin/renderer/debug/librenderer.a
LIBS += ../../renderer/third-party/lib/mingw/libyaml-cpp.a
LIBS += $(BOOST_ROOT)/stage/lib/libboost_filesystem-mgw46-1_49.a
LIBS += $(BOOST_ROOT)/stage/lib/libboost_system-mgw46-1_49.a

LIBS += -lgdi32
LIBS += -lkernel32
LIBS += -luser32
LIBS += -lcomctl32

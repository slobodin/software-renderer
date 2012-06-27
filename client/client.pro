TEMPLATE = app
CONFIG += console
CONFIG -= qt

QMAKE_CXXFLAGS += -std=gnu++0x

HEADERS += \
    windowsviewport.h \
    windowsapplication.h

SOURCES += \
    windowsviewport.cpp \
    windowsapplication.cpp \
    main.cpp

INCLUDEPATH += ../renderer/base \
               ../renderer/comm \
               ../renderer/math \
               ../renderer/rend \
               ../renderer/ \
               $(BOOST_ROOT)

win32:LIBS += ../../bin/renderer/debug/librenderer.a
win32:LIBS += $(BOOST_ROOT)/stage/lib/libboost_filesystem-mgw46-1_49.a
win32:LIBS += $(BOOST_ROOT)/stage/lib/libboost_system-mgw46-1_49.a
win32:LIBS += ../../renderer/third-party/lib/libyaml-cpp.a

LIBS += -lgdi32
LIBS += -lkernel32
LIBS += -luser32
LIBS += -lcomctl32

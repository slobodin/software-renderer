TEMPLATE = app
CONFIG += console
CONFIG -= qt

QMAKE_CXXFLAGS += -std=gnu++0x

INCLUDEPATH += ../renderer/base \
               ../renderer/comm \
               ../renderer/math \
               ../renderer/rend \
               ../renderer/ \
               $(BOOST_ROOT)

HEADERS += \
    windowsviewport.h \
    windowsapplication.h

SOURCES += \
    windowsviewport.cpp \
    windowsapplication.cpp \
    main.cpp

win32:LIBS += d:/srend/software-renderer/bin/renderer/debug/librenderer.a
win32:LIBS += $(BOOST_ROOT)/stage/lib/libboost_filesystem-mgw46-1_49.a
win32:LIBS += $(BOOST_ROOT)/stage/lib/libboost_system-mgw46-1_49.a
win32:LIBS += d:/srend/software-renderer/renderer/third-party/lib/libyaml-cpp.a

LIBS += -lgdi32
LIBS += -lkernel32
LIBS += -luser32
LIBS += -lcomctl32

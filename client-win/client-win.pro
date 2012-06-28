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

LIBS += $(BOOST_ROOT)/stage/lib/libboost_filesystem-mgw46-1_49.a
LIBS += $(BOOST_ROOT)/stage/lib/libboost_system-mgw46-1_49.a
LIBS += ../../renderer/third-party/lib/libyaml-cpp.a
LIBS += ../../bin/renderer/debug/librenderer.a

LIBS += -lgdi32
LIBS += -lkernel32
LIBS += -luser32
LIBS += -lcomctl32

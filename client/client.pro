QMAKE_CXXFLAGS += -std=c++0x

HEADERS += \
    application.h

SOURCES += \
    application.cpp

INCLUDEPATH += ../renderer/base \
               ../renderer/comm \
               ../renderer/math \
               ../renderer/rend \
               ../renderer/

LIBS += -L../renderer-debug/ -lrenderer
LIBS += -lyaml-cpp

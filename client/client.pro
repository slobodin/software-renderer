QMAKE_CXXFLAGS += -std=c++0x
DEFINES += CLIENT_MAIN

HEADERS += \
    application.h \
    clientcontroller.h

SOURCES += \
    application.cpp \
    clientcontroller.cpp

INCLUDEPATH += ../renderer/base \
               ../renderer/comm \
               ../renderer/math \
               ../renderer/rend \
               ../renderer/ \
                /usr/include/tcl8.5 \
                /usr/include

LIBS += -L../renderer-debug/ -lrenderer

OTHER_FILES += \
    ../README

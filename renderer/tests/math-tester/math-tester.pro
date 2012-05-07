TEMPLATE = app
CONFIG += console
CONFIG -= qt
QMAKE_CXXFLAGS += -std=c++0x

SOURCES += main.cpp \
    test_vec_matr_2x2.cpp \
    test_vec_matr_3x3.cpp \
    ../../math/m44.cpp \
    test_vec_matr_4x4.cpp \
    test_math_utils.cpp \
    ../../math/math_utils.cpp \
    test_plane.cpp \
    ../../math/plane.cpp

INCLUDEPATH += ../../math/ \
               ../../comm/

SOURCES += ../../math/m33.cpp

LIBS += -lgtest -lgtest_main -lpthread

HEADERS += \
    ../../math/m44.h \
    ../../math/m33.h \
    ../../math/m22.h \
    ../../math/math_utils.h \
    ../../math/plane.h


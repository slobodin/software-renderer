TEMPLATE = app
CONFIG += console
CONFIG -= qt
QMAKE_CXXFLAGS += -std=c++0x

SOURCES += main.cpp \
    test_vec_matr_2x2.cpp \
    test_vec_matr_3x3.cpp

INCLUDEPATH += ../../math/ \
               ../../comm/

SOURCES += ../../math/m33.cpp

LIBS += -lgtest -lgtest_main -lpthread


TEMPLATE = app
CONFIG += console
CONFIG -= qt
QMAKE_CXXFLAGS += -std=c++0x

SOURCES += main.cpp \
    test_vec_matr_2x2.cpp

INCLUDEPATH += ../../math/ \
               ../../comm/

LIBS += -lgtest -lgtest_main -lpthread


TEMPLATE    = lib
LANGUAGE    = C++
CONFIG      += console precompile_header

PRECOMPILED_HEADER = comm/comm_pch.h

precompile_header:!isEmpty(PRECOMPILED_HEADER) {
DEFINES += USING_PCH
}

Debug:DEFINES += DEBUG

QMAKE_CXXFLAGS += -std=c++0x

HEADERS += \
    math/vec3.h \
    math/vec2.h \
    math/common_math.h \
    comm/string_utils.h \
    comm/comm_macro.h \
    comm/comm_pch.h \
    base/controller.h \
    base/decoderplg.h \
    base/logger.h \
    base/osfile.h \
    base/ospath.h \
    base/resource.h \
    base/resourcedecoder.h \
    base/resourcemgr.h \
    comm/exception.h \
    comm/singleton.h \
    math/affinetransform.h \
    math/m22.h \
    math/m33.h \
    rend/boundingsphere.h \
    rend/camera.h \
    rend/mesh.h \
    math/plane.h \
    rend/rendermgr.h \
    dll.h \
    rend/rasterizer.h \
    third-party/cpptk-1.0.2/cpptk.h \
    third-party/cpptk-1.0.2/base/cpptkbase.h \
    rend/framebuffer.h \
    rend/color.h \
    math/poly.h \
    base/config.h \
    rend/material.h \
    rend/light.h \
    rend/renderlist.h \
    base/decoderbspq3.h

SOURCES += \
    comm/string_utils.cpp \
    base/controller.cpp \
    base/decoderplg.cpp \
    base/logger.cpp \
    base/osfile.cpp \
    base/ospath.cpp \
    base/resourcemgr.cpp \
    math/affinetransform.cpp \
    math/m33.cpp \
    math/plane.cpp \
    rend/boundingsphere.cpp \
    rend/camera.cpp \
    rend/mesh.cpp \
    rend/rendermgr.cpp \
    rend/rasterizer.cpp \
    third-party/cpptk-1.0.2/cpptk.cc \
    third-party/cpptk-1.0.2/base/cpptkbase.cc \
    rend/framebuffer.cpp \
    rend/color.cpp \
    math/poly.cpp \
    base/config.cpp \
    rend/material.cpp \
    rend/light.cpp \
    rend/renderlist.cpp \
    base/decoderbspq3.cpp

INCLUDEPATH += ./base \
                ./comm \
                ./math \
                ./rend \
                /usr/include/tcl8.5 \
                /usr/include

LIBS += -ltcl8.5
LIBS += -ltk8.5
LIBS += -lyaml-cpp

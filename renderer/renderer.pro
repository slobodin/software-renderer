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
    rend/color4.h \
    rend/mesh.h \
    math/plane.h \
    rend/rendermgr.h \
    dll.h \
    rend/rasterizer.h

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
    rend/color4.cpp \
    rend/mesh.cpp \
    rend/rendermgr.cpp \
    rend/rasterizer.cpp

INCLUDEPATH += ./base \
                ./comm \
                ./math \
                ./rend

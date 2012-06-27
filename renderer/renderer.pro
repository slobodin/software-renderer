TEMPLATE    = lib
LANGUAGE    = C++
CONFIG      += console precompile_header staticlib

PRECOMPILED_HEADER = comm/comm_pch.h

precompile_header:!isEmpty(PRECOMPILED_HEADER) {
DEFINES += USING_PCH
}

Debug:DEFINES += DEBUG
DEFINES += RENDERER_LIBRARY

QMAKE_CXXFLAGS += -std=gnu++0x

HEADERS += \
    base/resourcemgr.h \
    base/resourcedecoder.h \
    base/resource.h \
    base/osfile.h \
    base/logger.h \
    base/decoderplg.h \
    base/decoderbspq3.h \
    base/decoderasc.h \
    base/controller.h \
    base/config.h \
    comm/string_utils.h \
    comm/singleton.h \
    comm/exception.h \
    comm/comm_pch.h \
    comm/comm_macro.h \
    math/vertex.h \
    math/vec3.h \
    math/vec2.h \
    math/poly.h \
    math/plane.h \
    math/math_utils.h \
    math/m44.h \
    math/m33.h \
    math/m22.h \
    math/common_math.h \
    rend/viewport.h \
    rend/vertexbuffer.h \
    rend/texture.h \
    rend/sceneobject.h \
    rend/rendermgr.h \
    rend/renderlist.h \
    rend/rasterizer.h \
    rend/node.h \
    rend/mesh.h \
    rend/material.h \
    rend/light.h \
    rend/framebuffer.h \
    rend/color.h \
    rend/camera.h \
    rend/boundingsphere.h \
    platform/events.h \
    platform/baseapp.h \
    renderer.h

SOURCES += \
    base/resourcemgr.cpp \
    base/osfile.cpp \
    base/logger.cpp \
    base/decoderplg.cpp \
    base/decoderbspq3.cpp \
    base/decoderasc.cpp \
    base/controller.cpp \
    base/config.cpp \
    comm/string_utils.cpp \
    math/vertex.cpp \
    math/poly.cpp \
    math/plane.cpp \
    math/math_utils.cpp \
    math/m44.cpp \
    math/m33.cpp \
    rend/viewport.cpp \
    rend/vertexbuffer.cpp \
    rend/texture.cpp \
    rend/sceneobject.cpp \
    rend/rendermgr.cpp \
    rend/renderlist.cpp \
    rend/rasterizer.cpp \
    rend/mesh.cpp \
    rend/material.cpp \
    rend/light.cpp \
    rend/framebuffer.cpp \
    rend/color.cpp \
    rend/camera.cpp \
    rend/boundingsphere.cpp \
    platform/baseapp.cpp

INCLUDEPATH += ./base \
                ./comm \
                ./math \
                ./rend \
                ./third-party/include/ \
                $(BOOST_ROOT)

win32:LIBS += d:/srend/software-renderer/renderer/third-party/lib/libyaml-cpp.a
win32:LIBS += $(BOOST_ROOT)/stage/lib/libboost_filesystem-mgw46-mt-1_49.a
win32:LIBS += $(BOOST_ROOT)/stage/lib/libboost_system-mgw46-mt-1_49.a

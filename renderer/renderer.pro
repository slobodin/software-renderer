QT          += core
TEMPLATE    = lib
LANGUAGE    = C++
CONFIG      += console precompile_header

PRECOMPILED_HEADER = comm/comm_pch.h

precompile_header:!isEmpty(PRECOMPILED_HEADER) {
DEFINES += USING_PCH
}

Debug:DEFINES += DEBUG
DEFINES += RENDERER_LIBRARY

QMAKE_CXXFLAGS += -std=gnu++0x

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
    base/resource.h \
    base/resourcedecoder.h \
    base/resourcemgr.h \
    comm/exception.h \
    comm/singleton.h \
    math/m22.h \
    math/m33.h \
    rend/boundingsphere.h \
    rend/camera.h \
    rend/mesh.h \
    math/plane.h \
    rend/rendermgr.h \
    dll.h \
    rend/rasterizer.h \
    rend/framebuffer.h \
    rend/color.h \
    math/poly.h \
    base/config.h \
    rend/material.h \
    rend/light.h \
    rend/renderlist.h \
    base/decoderbspq3.h \
    base/decoderasc.h \
    math/vertex.h \
    rend/texture.h \
    math/math_utils.h \
    math/m44.h \
    rend/vertexbuffer.h \
    platform/baseappqt.h \
    platform/baseapptk.h \
    platform/baseapp.h \
    rend/viewport.h \
    rend/node.h \
    rend/sceneobject.h \
    renderer.h

SOURCES += \
    comm/string_utils.cpp \
    base/controller.cpp \
    base/decoderplg.cpp \
    base/logger.cpp \
    base/osfile.cpp \
    base/resourcemgr.cpp \
    math/m33.cpp \
    math/plane.cpp \
    rend/boundingsphere.cpp \
    rend/camera.cpp \
    rend/mesh.cpp \
    rend/rendermgr.cpp \
    rend/rasterizer.cpp \
    rend/framebuffer.cpp \
    rend/color.cpp \
    math/poly.cpp \
    base/config.cpp \
    rend/material.cpp \
    rend/light.cpp \
    rend/renderlist.cpp \
    base/decoderbspq3.cpp \
    base/decoderasc.cpp \
    math/vertex.cpp \
    rend/texture.cpp \
    math/math_utils.cpp \
    math/m44.cpp \
    rend/vertexbuffer.cpp \
    platform/baseappqt.cpp \
    platform/baseapptk.cpp \
    rend/viewport.cpp \
    rend/sceneobject.cpp

INCLUDEPATH += ./base \
                ./comm \
                ./math \
                ./rend \
                ./third-party/include/ \
                $(BOOST_ROOT)

win32:LIBS += d:\srend\software-renderer\renderer\third-party\lib\libyaml-cpp.a
win32:LIBS += -L$(BOOST_ROOT)\stage\lib\ -lboost_filesystem-mgw46-mt-1_49 -lboost_system-mgw46-mt-1_49

TEMPLATE    = lib
LANGUAGE    = C++
CONFIG      += console precompile_header staticlib

PRECOMPILED_HEADER = comm/comm_pch.h

precompile_header:!isEmpty(PRECOMPILED_HEADER) {
DEFINES += USING_PCH
}

Debug:DEFINES += DEBUG
DEFINES += RENDERER_LIBRARY
win32:DEFINES += WINDOWS_VERSION
unix:DEFINES += LINUX_VERSION
DEFINES += TK_VERSION

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
    renderer.h \
    base/decoderobj.h \
    base/decoder3ds.h \
    base/decodermd2.h \
    platform/baseapplinux.h \
    third-party/include/cpptk-1.0.2/base/cpptkbase.h \
    third-party/include/cpptk-1.0.2/cpptk.h \
    platform/baseapptk.h \
    base/decodercob.h

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
    platform/baseapp.cpp \
    platform/events.cpp \
    base/decoderobj.cpp \
    base/decoder3ds.cpp \
    base/decodermd2.cpp \
    platform/baseapplinux.cpp \
    platform/baseapptk.cpp \
    third-party/include/cpptk-1.0.2/cpptk.cc \
    third-party/include/cpptk-1.0.2/base/cpptkbase.cc \
    base/decodercob.cpp

INCLUDEPATH += ./base \
                ./comm \
                ./math \
                ./rend \
                /usr/include/tcl8.5/ \
                ./third-party/include/ \
                $(BOOST_ROOT) \

win32:LIBS += ./third-party/lib/mingw/libyaml-cpp.a
win32:LIBS += $(BOOST_ROOT)/stage/lib/libboost_filesystem-mgw46-mt-1_49.a
win32:LIBS += $(BOOST_ROOT)/stage/lib/libboost_system-mgw46-mt-1_49.a

OTHER_FILES += \
    third-party/include/cpptk-1.0.2/cpptkoptions.x \
    third-party/include/cpptk-1.0.2/cpptkconstants.x

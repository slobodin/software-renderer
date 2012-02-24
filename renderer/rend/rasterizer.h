#ifndef RASTERIZER_H
#define RASTERIZER_H

#include "comm_pch.h"

#include "mesh.h"
#include "camera.h"
#include "color.h"
#include "framebuffer.h"

namespace rend
{

class Rasterizer
{
    FrameBuffer m_fb;

    // helpers
    void drawFillTriangle(const math::vec3 &p1,
                          const math::vec3 &p2,
                          const math::vec3 &p3,
                          const Color3 &color);
    void drawTriangle(const math::vec3 &p1,
                      const math::vec3 &p2,
                      const math::vec3 &p3,
                      const Color3 &color);
    void drawBottomTriangle(int x1, int y1,
                            int x2, int y2,
                            int x3, int y3,
                            const Color3 &color);
    void drawTopTriangle(int x1, int y1,
                         int x2, int y2,
                         int x3, int y3,
                         const Color3 &color);
    bool clipLine(math::vec3 &p1, math::vec3 &p2);
    void drawLine(const math::vec3 &p1,
                  const math::vec3 &p2,
                  const Color3 &color);

public:
    Rasterizer(const int width, const int height);

    void draw(const SPTR(Mesh) mesh, const SPTR(Camera) cam);

    void beginFrame();
    void endFrame(const string &to);
};

}

#endif // RASTERIZER_H

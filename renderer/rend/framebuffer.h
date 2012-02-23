#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include "color.h"

namespace rend
{

class Rasterizer;

class FrameBuffer
{
    friend class Rasterizer;

    Color3 *m_pixels;
    int m_width;
    int m_height;
    int m_xOrigin;
    int m_yOrigin;

    FrameBuffer(const int witdh,
                const int height);
    ~FrameBuffer();

    void clear();
    void flush_tk();
    void flush_win();
    void flush_gl();
    void scanline(const int x1, const int x2,
                  const int y, const Color3 &color);
};

}

#endif // FRAMEBUFFER_H

/*
 * framebuffer.h
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include "comm_pch.h"

#include "color.h"

namespace rend
{

class Rasterizer;

class FrameBuffer
{
    friend class Rasterizer;

    struct rgb { uint8_t r; uint8_t g; uint8_t b; } *m_pixels;
    int m_width;
    int m_height;
    int m_xOrigin;
    int m_yOrigin;

    FrameBuffer(const int witdh,
                const int height);
    ~FrameBuffer();

    void clear();
    void flush_tk(const string &to);
    void flush_win();
    void flush_gl();
    void wscanline(const int x1, const int x2,
                   const int y, const Color3 &color);
    void wpixel(const int x, const int y,
                const Color3 &color);
    void wpixel(const int pos, const Color3 &color);
};

}

#endif // FRAMEBUFFER_H

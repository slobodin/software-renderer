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

class FrameBuffer
{
public:
    struct rgb
    {
//        uint8_t unused;
        uint8_t r;
        uint8_t g;
        uint8_t b;
        rgb() : /*unused(0xFF), */r(0x00), g(0x00), b(0x00) { }
    }/* __attribute__((packed))*/;

private:
    rgb *m_pixels;

    int m_width;
    int m_height;
    int m_xOrigin;
    int m_yOrigin;

public:
    FrameBuffer(const int witdh,
                const int height);
    ~FrameBuffer();

    void clear();

    void wscanline(const int x1, const int x2,
                   const int y, const Color3 &color);
    void wpixel(const int x, const int y,
                const Color3 &color);
    void wpixel(const int pos, const Color3 &color);

    void setWidth(int width) { m_width = width; }
    void setHeight(int height) { m_height = height; }

    int width() const { return m_width; }
    int height() const { return m_height; }

    int xorig() const { return m_xOrigin; }
    int yorig() const { return m_yOrigin; }

    void resize(int w, int h);

//    rgb *pixels() { return m_pixels; }
    operator unsigned char *() { return reinterpret_cast<unsigned char *>(m_pixels); }
};

inline void FrameBuffer::wscanline(const int x1, const int x2, const int y, const Color3 &color)
{
    if (x1 > x2)
        return;

    for (int x = x1; x <= x2; x++)
        wpixel(x, y, color);            // TODO: block putting!
}

inline void FrameBuffer::wpixel(const int x, const int y, const Color3 &color)
{
    if (!(x >= 0 && x < m_width && y >= 0 && y < m_height))
        return;         // do not need this condition

    m_pixels[m_width * y + x].r = color[RED];
    m_pixels[m_width * y + x].g = color[GREEN];
    m_pixels[m_width * y + x].b = color[BLUE];
}

inline void FrameBuffer::wpixel(const int pos, const Color3 &color)
{
    if (!(pos >= 0 && pos < (m_width * m_height)))
        return;

    m_pixels[pos].r = color[RED];
    m_pixels[pos].g = color[GREEN];
    m_pixels[pos].b = color[BLUE];
}

}

#endif // FRAMEBUFFER_H

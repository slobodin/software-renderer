/*
 * framebuffer.cpp
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#include "framebuffer.h"

#include <QImage>
#include <QRgb>

namespace rend
{

FrameBuffer::FrameBuffer(const int witdh, const int height)
    : m_pixels(0),
      m_width(witdh),
      m_height(height),
      m_xOrigin(0),
      m_yOrigin(0)
{
    m_pixels = new rgb[m_width * m_height];
}

FrameBuffer::~FrameBuffer()
{
    if (m_pixels)
        delete [] m_pixels;
}

void FrameBuffer::clear()
{
    memset(m_pixels, 0x00, sizeof(rgb) * m_width * m_height);
}

void FrameBuffer::wscanline(const int x1, const int x2, const int y, const Color3 &color)
{
    if (x1 > x2)
        return;

    for (int x = x1; x <= x2; x++)
    {
        wpixel(x, y, color);
    }
}

void FrameBuffer::wpixel(const int x, const int y, const Color3 &color)
{
    if (!(x >= 0 && x < m_width && y >= 0 && y < m_height))
        return;

    m_pixels[m_width * y + x].r = color[RED];
    m_pixels[m_width * y + x].g = color[GREEN];
    m_pixels[m_width * y + x].b = color[BLUE];
//    m_pixels[m_width * y + x].r = color[BLUE];
//    m_pixels[m_width * y + x].g = color[GREEN];
//    m_pixels[m_width * y + x].b = color[RED];
//    m_pixels[m_width * y + x].unused = 0xFF;
}

void FrameBuffer::wpixel(const int pos, const Color3 &color)
{
    if (!(pos >= 0 && pos < (m_width * m_height)))
        return;

    m_pixels[pos].r = color[RED];
    m_pixels[pos].g = color[GREEN];
    m_pixels[pos].b = color[BLUE];
//    m_pixels[pos].r = color[BLUE];
//    m_pixels[pos].g = color[GREEN];
//    m_pixels[pos].b = color[RED];
//    m_pixels[pos].unused = 0xFF;
}

void FrameBuffer::resize(int w, int h)
{
    m_width = w;
    m_height = h;

    if (m_pixels)
        delete [] m_pixels;

    m_pixels = new FrameBuffer::rgb[m_width * m_height];
    memset(m_pixels, 0x00, sizeof(FrameBuffer::rgb) * m_width * m_height);
}

}

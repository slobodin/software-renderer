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

// this function fills or sets unsigned 32-bit aligned memory
// count is number of quads
static inline void Memset_QUAD(void *dest, const uint32_t data, int count)
{
    __asm__ ("mov %%edi, %0\n\t" ::"d"(dest));
    __asm__ ("mov %%ecx, %0\n\t" ::"d"(count));
    __asm__ ("mov %%eax, %0\n\t" ::"d"(data));
    __asm__ ("rep stosd");
//             "mov %ecx, count\n\t"
//             "mov %eax, data\n\t"
//             "rep stosd");
//    __asm
//    {
//        mov edi, dest   ; edi points to destination memory
//        mov ecx, count  ; number of 32-bit words to move
//        mov eax, data   ; 32-bit data
//        rep stosd       ; move data
//    }
}

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

    // FIXME: quad memset
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
}

void FrameBuffer::wpixel(const int pos, const Color3 &color)
{
    if (!(pos >= 0 && pos < (m_width * m_height)))
        return;

    m_pixels[pos].r = color[RED];
    m_pixels[pos].g = color[GREEN];
    m_pixels[pos].b = color[BLUE];
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

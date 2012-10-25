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

//! Fills memory with 32bit values.
void memset32(void *dest, uint32_t data, int count);

//! Wrapper under pixel and z buffers.
/*!
  *
  */
class FrameBuffer : boost::noncopyable
{
public:
    struct rgb
    {
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;

        rgb(uint8_t R = 0x00, uint8_t G = 0x00, uint8_t B = 0x00) : r(R), g(G), b(B), a(255) { }
    } __attribute__((packed));

private:
    //! Pixels array.
    rgb *m_pixels;
    //! Z Buffer contains 1/z values (in order to perform perspective correct rasterization).
    float *m_zbuffer;

    int m_width;
    int m_height;
    int m_xOrigin;
    int m_yOrigin;
    int m_size;

    void blendAndStore(int pos, uint8_t r, uint8_t g, uint8_t b, int alpha = 255)
    {
        static float a, oneMinusAlpha;

        rgb &currPix = m_pixels[pos];

        if (alpha == 255)
        {
            m_pixels[pos].r = r;
            m_pixels[pos].g = g;
            m_pixels[pos].b = b;
        }
        else
        {
            a = alpha / 255.0f;
            oneMinusAlpha = (255 - alpha) / 255.0f;

            m_pixels[pos].r = a * r + oneMinusAlpha * currPix.r;
            m_pixels[pos].g = a * g + oneMinusAlpha * currPix.g;
            m_pixels[pos].b = a * b + oneMinusAlpha * currPix.b;
        }
    }

public:
    FrameBuffer(int w, int h);
    ~FrameBuffer();

    void clear();

    void wscanline(const int x1, const int x2,
                   const int y, const Color3 &color);
    void wpixel(const int x, const int y, const Color3 &color, int alpha = 255);
    void wpixel(const int pos, const Color3 &color, int alpha = 255);
    void wpixel(const int x, const int y, const Color3 &color, float z, int alpha = 255);

    void setWidth(int width) { m_width = width; }
    void setHeight(int height) { m_height = height; }

    int width() const { return m_width; }
    int height() const { return m_height; }

    int xorig() const { return m_xOrigin; }
    int yorig() const { return m_yOrigin; }

    void resize(int w, int h);

    operator unsigned char *() { return reinterpret_cast<unsigned char *>(m_pixels); }
};

inline void FrameBuffer::wscanline(const int x1, const int x2, const int y, const Color3 &color)
{
    if (x1 > x2)
        return;

    memset32(m_pixels + m_width * y + x1,
             RgbToInt(color[BLUE], color[GREEN], color[RED]),
             x2 - x1 + 1);
    /*for (int x = x1; x <= x2; x++)
        wpixel(x, y, color);*/
}

inline void FrameBuffer::wpixel(const int x, const int y, const Color3 &color, int alpha)
{
    if (!(x >= 0 && x < m_width && y >= 0 && y < m_height))
        return;

    int pos = m_width * y + x;

    blendAndStore(pos, color[RED], color[GREEN], color[BLUE], alpha);
}

inline void FrameBuffer::wpixel(const int x, const int y, const Color3 &color, float z, int alpha)
{
    static float a, oneMinusAlpha;

    if (!(x >= 0 && x < m_width && y >= 0 && y < m_height))
        return;

    int pos = m_width * y + x;

    rgb &currPix = m_pixels[pos];

    if (alpha == 255)
    {
        if (z > m_zbuffer[pos])         // NOTE: this is 1/z buffer
        {
            m_pixels[pos].r = color[RED];
            m_pixels[pos].g = color[GREEN];
            m_pixels[pos].b = color[BLUE];
            m_zbuffer[pos] = z;
        }
    }
    else
    {
        a = alpha / 255.0f;
        oneMinusAlpha = (255 - alpha) / 255.0f;

        m_pixels[pos].r = a * color[RED] + oneMinusAlpha * currPix.r;
        m_pixels[pos].g = a * color[GREEN] + oneMinusAlpha * currPix.g;
        m_pixels[pos].b = a * color[BLUE] + oneMinusAlpha * currPix.b;
    }
}

inline void FrameBuffer::wpixel(const int pos, const Color3 &color, int alpha)
{
    if (pos < 0 || pos >= m_size)
        return;

    blendAndStore(pos, color[RED], color[GREEN], color[BLUE], alpha);
}

}

#endif // FRAMEBUFFER_H

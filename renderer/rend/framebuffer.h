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

class QImage;

namespace rend
{

class FrameBuffer
{
public:
    struct rgb { uint8_t r; uint8_t g; uint8_t b; };

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

    rgb *pixels() { return m_pixels; }
};

}

#endif // FRAMEBUFFER_H

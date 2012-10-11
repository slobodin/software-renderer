/*
 * framebuffer.cpp
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#include "framebuffer.h"

namespace rend
{

FrameBuffer::FrameBuffer(int witdh, int height)
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

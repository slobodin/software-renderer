/*
 * texture.cpp
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#include "texture.h"

namespace rend
{

Texture::Texture(unsigned char *pixels, int width, int height, int bpp)
    : m_pixels(0),
      m_width(0),
      m_height(0),
      m_bpp(bpp)
{
    // allocate mem
    int size = sizeof(unsigned char) * width * height * bpp;

    m_pixels = new unsigned char[size];

    // store pixels
    memcpy(m_pixels, pixels, size);

    m_width = width;
    m_height = height;
}

Texture::~Texture()
{
    if (m_pixels)
        delete [] m_pixels;
}

}

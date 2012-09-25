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

Color3 Texture::at(int x, int y) const
{
    if (x >= m_width || y >= m_height/* || x < 0 || y < 0*/)
        return Color3();//throw TextureException("Out of range while getting texel.");

    unsigned char *col = m_pixels + y * m_width + x;

    if (m_bpp == 3)
        return Color3(col[0], col[1], col[2]);
    else if (m_bpp == 1)
        return Color3(col[0], col[0], col[0]);      // !!!!
    else
        throw std::exception();
}

Color3 Texture::at(int pos) const
{
    unsigned char *col = m_pixels + pos;

    return Color3(col[0], col[1], col[2]);
}

}

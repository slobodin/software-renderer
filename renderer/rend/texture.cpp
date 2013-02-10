/*
 * texture.cpp
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#include "stdafx.h"

#include "texture.h"

namespace rend
{

const Color3 Texture::BLACK;

Texture::Texture(const std::vector<Color3> &pixels, int width, int height)
    : m_pixels(pixels),
      m_width(width),
      m_height(height)
{
}

Texture::~Texture()
{
}

std::vector<Color3> Texture::getLine(int y, int xStart, int xEnd) const
{
    std::vector<Color3> retRes;
    if (y >= m_height || xStart >= m_width || xStart > xEnd)
        return retRes;

    retRes.assign(m_pixels.begin() + y * m_width + xStart,
                  m_pixels.begin() + y * m_width + (xEnd == 0 ? m_width : xEnd));

    return retRes;
}

std::vector<Color3> Texture::getBlock(int x, int y, int width, int height) const
{
    std::vector<Color3> retRes;
    if (x >= m_width || y >= m_height)
        return retRes;
    if (((x + width) >= m_width) || ((y + height) >= m_height))
        return retRes;

    retRes.reserve(width * height);

    for (int l = y; l < y + height; l++)
    {
        auto lnOfPixels = getLine(l, x, x + width);
        retRes.insert(retRes.end(), lnOfPixels.begin(), lnOfPixels.end());
    }

    return retRes;
}

sptr(Texture) Texture::clone() const
{
    return std::make_shared<Texture>(m_pixels, m_width, m_height);
}

}

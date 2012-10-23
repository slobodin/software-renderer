/*
 * texture.h
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#ifndef TEXTURE_H
#define TEXTURE_H

#include "resource.h"
#include "color.h"

namespace rend
{

DECLARE_EXCEPTION(TextureException)

class Texture : public base::Resource
{
    vector<Color4> m_pixels;
    static const Color4 BLACK;

    int m_width, m_height;

public:
    Texture(const vector<Color4> &pixels, int width, int height);
    ~Texture();

    const Color4 &at(int x, int y) const
    {
        if (x >= m_width || y >= m_height || x < 0 || y < 0)
            return BLACK;//throw TextureException("Out of range while getting texel.");

        return m_pixels[y * m_width + x];
    }

    const Color4 &at(int pos) const
    {
        if (pos < 0 || pos >= (m_width * m_height))
            return BLACK;

        return m_pixels[pos];
    }

    // Getting pixels
    vector<Color4> getLine(int y, int xStart = 0, int xEnd = 0) const;
    vector<Color4> getBlock(int x, int y, int width, int height) const;

    const Color4 *raw() const
    {
        return &m_pixels[0];
    }

    int width() const { return m_width; }
    int height() const { return m_height; }

    sptr(Texture) clone() const;
};

}

#endif // TEXTURE_H

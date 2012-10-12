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
    vector<Color3> m_pixels;

    int m_width, m_height;
public:
    Texture(const vector<Color3> &pixels, int width, int height);
    ~Texture();

    Color3 at(int x, int y) const
    {
        if (x >= m_width || y >= m_height || x < 0 || y < 0)
            return Color3();//throw TextureException("Out of range while getting texel.");

        return m_pixels[y * m_width + x];
    }

    Color3 at(int pos) const
    {
        if (pos < 0 || pos >= (m_width * m_height))
            return Color3();

        return m_pixels[pos];
    }

    const Color3 *raw() const
    {
        return &m_pixels[0];
    }

    int width() const { return m_width; }
    int height() const { return m_height; }
};

}

#endif // TEXTURE_H

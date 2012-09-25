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
    unsigned char *m_pixels;

    int m_width, m_height;

public:
    Texture(unsigned char *pixels, int width, int height);
    ~Texture();

    Color3 at(int x, int y) const;
    Color3 at(int pos) const;

    int width() const { return m_width; }
    int height() const { return m_height; }
};

}

#endif // TEXTURE_H

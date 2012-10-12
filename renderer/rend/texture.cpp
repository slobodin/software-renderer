/*
 * texture.cpp
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#include "texture.h"

namespace rend
{

Texture::Texture(const vector<Color3> &pixels, int width, int height)
    : m_pixels(pixels),
      m_width(width),
      m_height(height)
{
}

Texture::~Texture()
{
}

}

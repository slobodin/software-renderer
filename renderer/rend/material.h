/*
 * material.h
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#ifndef MATERIAL_H
#define MATERIAL_H

#include "comm_pch.h"

#include "color.h"
#include "texture.h"

namespace rend
{

class Material
{
public:
    enum ShadeMode
    {
        SM_FLAT,
        SM_GOURAUD,
        SM_PHONG,
        SM_WIRE,
        SW_TEXTURE,
        SM_UNDEFINED
    };

private:
    Color3 m_color;
    ShadeMode m_shadeMode;
    sptr(Texture) m_texture;

    // active, cliped, backface

public:
    Material();
    Material(const Color3 &color, ShadeMode shadeMode);

    const Color3 &color() const { return m_color; }
    Color3 &color() { return m_color; }

    ShadeMode shadeMode() const { return m_shadeMode; }
};

}

#endif // MATERIAL_H

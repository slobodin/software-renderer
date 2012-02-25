#ifndef MATERIAL_H
#define MATERIAL_H

#include "comm_pch.h"

#include "color.h"

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
        SM_WIRE
    };

private:
    Color3 m_color;
    ShadeMode m_shadeMode;

    // active, cliped, backface

public:
    Material(const Color3 &color, ShadeMode shadeMode);

    const Color3 &color() const { return m_color; }
    ShadeMode shadeMode() const { return m_shadeMode; }
};

}

#endif // MATERIAL_H

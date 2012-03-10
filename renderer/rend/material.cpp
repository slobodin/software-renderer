/*
 * material.cpp
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#include "material.h"

namespace rend
{

Material::Material()
    : m_shadeMode(SM_UNDEFINED)/*,
      m_sides(math::Triangle::ST_2_SIDED)*/
{
}

Material::Material(const Color3 &color, ShadeMode shadeMode)
    : m_color(color),
      m_shadeMode(shadeMode)/*,
      m_sides(sides)*/
{
}

}

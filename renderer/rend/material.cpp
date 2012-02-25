#include "material.h"

namespace rend
{

Material::Material(const Color3 &color, ShadeMode shadeMode)
    : m_color(color),
      m_shadeMode(shadeMode)
{
}

}

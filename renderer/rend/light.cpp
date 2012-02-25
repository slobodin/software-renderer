#include "light.h"

namespace rend
{

const size_t Light::MAX_LIGHTS = 8;
size_t Light::NumLights = 0;

Light::Light(const LightType &type, const math::vec3 pos, const math::vec3 &dir)
    : m_type(type),
      m_isEnabled(true),
      m_pos(pos),
      m_dir(dir)
{
    if (NumLights >= MAX_LIGHTS)
    {
        throw LightException("Light limit is reached");
    }

    NumLights++;
    m_dir.normalize();
}

Light::~Light()
{
    NumLights--;
}

}

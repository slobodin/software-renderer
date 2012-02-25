#include "light.h"

namespace rend
{

const size_t Light::MAX_LIGHTS = 8;
size_t Light::NumLights = 0;

Light::Light(const Color3 &intensity)
    : m_isEnabled(true),
      m_intensity(intensity)
{
    if (NumLights >= MAX_LIGHTS)
    {
        throw LightException("Light limit is reached");
    }

    NumLights++;
}

Light::~Light()
{
    NumLights--;
}

AmbientLight::AmbientLight(const Color3 &intensity)
    : Light(intensity)
{
}

void AmbientLight::illuminate() const
{
}

}

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

void AmbientLight::illuminate(RenderList &renderlist) const
{
    if (!m_isEnabled)
        return;

    Color3 shadedColor(0, 0, 0);
    list<math::Triangle> &trias = renderlist.triangles();
    list<math::Triangle>::iterator t = trias.begin();

    while (t != trias.end())
    {
        Material &material = t->material();

        if (material.shadeMode() == Material::SM_UNDEFINED
                || material.shadeMode() == Material::SM_WIRE)
        {
            t++;
            continue;
        }

        shadedColor.red() += m_intensity.red() * material.color().red() / 256;
        shadedColor.green() += m_intensity.green() * material.color().green() / 256;
        shadedColor.blue() += m_intensity.blue() * material.color().blue() / 256;

        material.color() = shadedColor;

        shadedColor.reset();
        t++;
    }
}

}

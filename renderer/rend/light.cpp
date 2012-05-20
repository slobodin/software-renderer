/*
 * light.cpp
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

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
        throw LightException("Light limit is reached");

    NumLights++;

    m_shader = &Light::shader;
}

Light::~Light()
{
    NumLights--;
}

void Light::illuminate(RenderList &renderlist) const
{
    /*if (!m_isEnabled)
        return;

    list<math::Triangle> &trias = renderlist.triangles();

    foreach (math::Triangle &t, trias)
    {
        Material &material = t.material();

        switch (material.shadeMode)
        {
        case Material::SM_FLAT:
            material.color() = m_shader(this, material.color(), t.normal());
            break;

        case Material::SM_GOURAUD:
            t.v(0).color = m_shader(this, t.v(0).color, t.v(0).n);
            t.v(1).color = m_shader(this, t.v(1).color, t.v(1).n);
            t.v(2).color = m_shader(this, t.v(2).color, t.v(2).n);
            break;

        case Material::SM_UNDEFINED:
        case Material::SM_WIRE:
        case Material::SW_TEXTURE:
        default:
            break;
        }
    }*/
}

Color3 AmbientLight::shader(const Color3 &matColor, const math::vec3 &/*normal*/) const
{
    Color3 shadedColor;
    shadedColor = m_intensity * matColor;
    shadedColor *= (1 / 256.0);

    return shadedColor;
}

AmbientLight::AmbientLight(const Color3 &intensity)
    : Light(intensity)
{
}

Color3 DirectionalLight::shader(const Color3 &matColor, const math::vec3 &normal) const
{
    Color3 shadedColor;
    const Color3 &originalColor = matColor;

    if (normal.isZero())
        return originalColor;

    double dp = normal.dotProduct(m_dir);
    if (dp > 0)
    {
        shadedColor = m_intensity * originalColor;
        shadedColor *= (dp / 256.0);
    }
    else
        return originalColor;

    return shadedColor;
}

DirectionalLight::DirectionalLight(const Color3 &intensity, const math::vec3 &dir)
    : Light(intensity),
      m_dir(dir)
{
    m_dir.normalize();
}

Color3 PointLight::shader(const Color3 &matColor, const math::vec3 &normal) const
{
    Color3 shadedColor;
    /*const Color3 &originalColor = t.material().color();

    if (t.normal().isZero())
        return originalColor;

    math::vec3 l = m_pos - t.v(0).p;
    double dist = l.length();

    double dp = t.normal().dotProduct(l);
    if (dp > 0)
    {
        double atten = m_kc + m_kl * dist + m_kq * dist * dist;
        double i = dp / (/*dist* atten);

        shadedColor = m_intensity * originalColor;
        shadedColor *= (i / 256.0);
    }
    else
        return originalColor;*/

    return shadedColor;
}

PointLight::PointLight(const Color3 &intensity, const math::vec3 &pos,
                       double kc, double kl, double kq)
    : Light(intensity),
      m_pos(pos),
      m_kc(kc),
      m_kl(kl),
      m_kq(kq)
{
}

Color3 SpotLight::shader(const Color3 &matColor, const math::vec3 &normal) const
{
}

SpotLight::SpotLight(const Color3 &intensity, const math::vec3 &pos, const math::vec3 &dir,
                     double umbra, double penumbra, double falloff)
    : Light(intensity),
      m_pos(pos),
      m_dir(dir),
      m_innerAngle(umbra),
      m_outerAngle(penumbra),
      m_falloff(falloff)
{
}

}

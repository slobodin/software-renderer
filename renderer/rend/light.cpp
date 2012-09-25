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

    m_lightId = NumLights;
    NumLights++;

    m_shader = &Light::shader;
}

Light::~Light()
{
    NumLights--;
}

void Light::illuminate(RenderList &renderlist) const
{
    if (!m_isEnabled)
        return;

    auto &trias = renderlist.triangles();

    for (auto &t : trias)
    {
        auto material = t.getMaterial();

        switch (material->shadeMode)
        {
        case Material::SM_FLAT:
//            t.v(0).color = t.v(1).color = t.v(2).color = m_shader(this, getMaterialColor(material), t.normal());
            t.v(0).color += m_shader(this, material, t.normal(), t.v(0).p);
            t.v(1).color += m_shader(this, material, t.normal(), t.v(0).p);
            t.v(2).color += m_shader(this, material, t.normal(), t.v(0).p);
            break;

        case Material::SM_GOURAUD:
            t.v(0).color += m_shader(this, material, t.v(0).n, t.v(0).p);
            t.v(1).color += m_shader(this, material, t.v(1).n, t.v(0).p);
            t.v(2).color += m_shader(this, material, t.v(2).n, t.v(0).p);
            break;

        case Material::SM_UNDEFINED:
        case Material::SM_PLAIN_COLOR:
        case Material::SM_WIRE:
            t.v(0).color = t.v(1).color = t.v(2).color = material->plainColor;
            break;
        case Material::SM_TEXTURE:
            // texture - performing standart flat shading. On rasterizing phaze we modulate texture texels with this color
            t.v(0).color += m_shader(this, material, t.normal(), t.v(0).p);
            t.v(1).color += m_shader(this, material, t.normal(), t.v(0).p);
            t.v(2).color += m_shader(this, material, t.normal(), t.v(0).p);
            break;
        default:
            break;
        }
    }
}

Color3 AmbientLight::shader(const sptr(Material) material, const math::vec3 &/*normal*/, const math::vec3 &/*pt*/) const
{
    Color3 shadedColor;
    shadedColor = m_intensity * material->ambientColor;
    shadedColor *= (1 / 256.0);     // no /= operator in Color3

    return shadedColor;
}

AmbientLight::AmbientLight(const Color3 &intensity)
    : Light(intensity)
{
}

Color3 DirectionalLight::shader(const sptr(Material) material, const math::vec3 &normal, const math::vec3 &/*pt*/) const
{
    Color3 shadedColor;

    if (normal.isZero())
        return Color3(0, 0, 0);

    double dp = normal.dotProduct(m_dir);
    if (dp > 0)
    {
        shadedColor = m_intensity * material->diffuseColor;
        shadedColor *= (dp / 256.0);
    }
    else
        return Color3(0, 0, 0);/*matColor*/;

    return shadedColor;
}

DirectionalLight::DirectionalLight(const Color3 &intensity, const math::vec3 &dir)
    : Light(intensity),
      m_dir(dir)
{
    m_dir.normalize();
}

Color3 PointLight::shader(const sptr(Material) material, const math::vec3 &normal, const math::vec3 &pt) const
{
    Color3 shadedColor;

    if (normal.isZero())
        return Color3(0, 0, 0);

    math::vec3 l = getPosition() - pt;
    double dist = l.length();

    double dp = normal.dotProduct(l);
    if (dp > 0)
    {
        double atten = m_kc + m_kl * dist + m_kq * dist * dist;
        double i = dp / (dist * atten);

        shadedColor = m_intensity * material->diffuseColor;
        shadedColor *= (i / 256.0);
    }
    else
        return Color3(0, 0, 0);

    return shadedColor;
}

PointLight::PointLight(const Color3 &intensity, const math::vec3 &pos,
                       double kc, double kl, double kq)
    : Light(intensity),
      m_kc(kc),
      m_kl(kl),
      m_kq(kq)
{
    setPosition(pos);
}
/*
Color3 SpotLight::shader(const Color3 &matColor, const math::vec3 &normal) const
{
    assert(false);  //  not working yet
}

Color3 SpotLight::getMaterialColor(sptr(Material) material) const
{
    return Color3();//material->ambientColor;
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
}*/

}

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

    int shadedColor_r = 0, shadedColor_g = 0, shadedColor_b = 0;
    list<math::Triangle> &trias = renderlist.triangles();

    foreach (math::Triangle &t, trias)
    {
        Material &material = t.material();

        if (material.shadeMode() == Material::SM_UNDEFINED
                || material.shadeMode() == Material::SM_WIRE)
            continue;

        // FIXME: for all light sources

        shadedColor_r += m_intensity.red() * material.color().red() / 256;
        shadedColor_g += m_intensity.green() * material.color().green() / 256;
        shadedColor_b += m_intensity.blue() * material.color().blue() / 256;

        if (shadedColor_r > 255) shadedColor_r = 255;
        if (shadedColor_g > 255) shadedColor_g = 255;
        if (shadedColor_b > 255) shadedColor_b = 255;

        material.color() = RgbToInt(shadedColor_r, shadedColor_g, shadedColor_b);

        shadedColor_r = 0;
        shadedColor_g = 0;
        shadedColor_b = 0;
    }
}

DirectionalLight::DirectionalLight(const Color3 &intensity, const math::vec3 &dir)
    : Light(intensity),
      m_dir(dir)
{
    m_dir.normalize();
}

void DirectionalLight::illuminate(RenderList &renderlist) const
{
    if (!m_isEnabled)
        return;

    int shadedColor_r = 0, shadedColor_g = 0, shadedColor_b = 0;
    list<math::Triangle> &trias = renderlist.triangles();

    foreach (math::Triangle &t, trias)
    {
        Material &material = t.material();

        if (material.shadeMode() == Material::SM_UNDEFINED
                || material.shadeMode() == Material::SM_WIRE)
            continue;

        if (t.normal().isZero())
            continue;

        double dp = t.normal().dotProduct(m_dir);
        if (dp > 0)
        {
            shadedColor_r += m_intensity.red() * dp * material.color().red() / 256;
            shadedColor_g += m_intensity.green() * dp * material.color().green() / 256;
            shadedColor_b += m_intensity.blue() * dp * material.color().blue() / 256;

            if (shadedColor_r > 255) shadedColor_r = 255;
            if (shadedColor_g > 255) shadedColor_g = 255;
            if (shadedColor_b > 255) shadedColor_b = 255;

            material.color() = RgbToInt(shadedColor_r, shadedColor_g, shadedColor_b);
        }

        shadedColor_r = 0;
        shadedColor_g = 0;
        shadedColor_b = 0;
    }
}

// FIXME: redo this boiler-plate ^
//                               |

}

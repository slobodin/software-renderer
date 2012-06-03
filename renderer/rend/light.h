/*
 * light.h
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#ifndef LIGHT_H
#define LIGHT_H

#include "comm_pch.h"

#include "vec3.h"
#include "color.h"
#include "renderlist.h"
#include "model.h"

namespace rend
{

DECLARE_EXCEPTION(LightException)

class Light : public Node
{
public:
    enum LightType
    {
        LT_AMBIENT_LIGHT,
        LT_DIRECTIONAL_LIGHT,
        LT_POINT_LIGHT,
        LT_SPOT_LIGHT
    };

    static const size_t MAX_LIGHTS;

private:
    static size_t NumLights;

protected:
    bool m_isEnabled;   // on\off
    Color3 m_intensity;

    virtual Color3 shader(const Color3 &matColor, const math::vec3 &normal) const = 0;

    typedef boost::function<Color3 (const Light*, const Color3 &, const math::vec3 &)> ShaderFunction;
    ShaderFunction m_shader;

    Light(const Color3 &intensity);
    virtual ~Light();

public:
    void turnon() { m_isEnabled = true; }
    void turnoff() { m_isEnabled = false; }

    virtual void illuminate(RenderList &renderlist) const;
};

//! Ambient light
class AmbientLight : public Light
{
protected:
    virtual Color3 shader(const Color3 &matColor, const math::vec3 &normal) const;

public:
    AmbientLight(const Color3 &intensity);
};

//! Directional light
class DirectionalLight : public Light
{
    math::vec3 m_dir;

    virtual Color3 shader(const Color3 &matColor, const math::vec3 &normal) const;

public:
    DirectionalLight(const Color3 &intensity, const math::vec3 &dir);
};

//! Point light
class PointLight : public Light
{
    math::vec3 m_pos;
    double m_kc, m_kl, m_kq;

    virtual Color3 shader(const Color3 &matColor, const math::vec3 &normal) const;

public:
    PointLight(const Color3 &intensity, const math::vec3 &pos,
               double kc, double kl, double kq);
};

//! Spot light
class SpotLight : public Light
{
    math::vec3 m_pos;
    math::vec3 m_dir;

    double m_innerAngle;    // spot inner angle
    double m_outerAngle;    // spot outer angle
    double m_falloff;

    virtual Color3 shader(const Color3 &matColor, const math::vec3 &normal) const;

public:
    SpotLight(const Color3 &intensity, const math::vec3 &pos, const math::vec3 &dir,
              double umbra, double penumbra, double falloff);
};

}

#endif // LIGHT_H

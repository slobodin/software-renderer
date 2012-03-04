#ifndef LIGHT_H
#define LIGHT_H

#include "comm_pch.h"

#include "vec3.h"
#include "color.h"
#include "renderlist.h"

namespace rend
{

DECLARE_EXCEPTION(LightException)

class Light
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

public:
    Light(const Color3 &intensity);
    virtual ~Light();

    void turnon() { m_isEnabled = true; }
    void turnoff() { m_isEnabled = false; }

    virtual void illuminate(RenderList &renderlist) const = 0;
};

class AmbientLight : public Light
{
public:
    AmbientLight(const Color3 &intensity);

    void illuminate(RenderList &renderlist) const;
};

class DirectionalLight : public Light
{
    math::vec3 m_dir;

public:
    DirectionalLight(const Color3 &intensity, const math::vec3 &dir);

    void illuminate(RenderList &renderlist) const;
};

}

#endif // LIGHT_H

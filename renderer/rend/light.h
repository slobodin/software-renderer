#ifndef LIGHT_H
#define LIGHT_H

#include "vec3.h"
#include "color.h"

namespace rend
{

DECLARE_EXCEPTION(LightException)

class Light
{
public:
    enum LightType
    {
        LT_AMBIENT_LIGHT,
        LT_DIRICTIONAL_LIGHT,
        LT_POINT_LIGHT,
        LT_SPOT_LIGHT
    };

    static const size_t MAX_LIGHTS;

private:
    static size_t NumLights;

    bool m_isEnabled;   // on\off

protected:
    Color3 m_intensity;

public:
    Light(const Color3 &intensity);
    virtual ~Light();

    void turnon() { m_isEnabled = true; }
    void turnoff() { m_isEnabled = false; }

    virtual void illuminate() const = 0;
};

class AmbientLight : public Light
{
public:
    AmbientLight(const Color3 &intensity);

    void illuminate() const;
};

}

#endif // LIGHT_H

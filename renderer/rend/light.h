#ifndef LIGHT_H
#define LIGHT_H

#include "vec3.h"

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

    LightType m_type;
    bool m_isEnabled;   // on\off

    math::vec3 m_pos;
    math::vec3 m_dir;

public:
    Light(const LightType &type, const math::vec3 pos, const math::vec3 &dir);
    ~Light();

    void turnon() { m_isEnabled = true; }
    void turnoff() { m_isEnabled = false; }
};

}

#endif // LIGHT_H

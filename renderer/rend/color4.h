#ifndef COLOR4_H
#define COLOR4_H

#include "comm_pch.h"

namespace rend
{

inline int RgbaToInt(int red, int green, int blue, int alpha)
{
    return blue | (green << 8) | (red << 16) | (alpha << 24);
}

class Color4
{
    uint8_t m_r;
    uint8_t m_g;
    uint8_t m_b;
    uint8_t m_a;

public:
    Color4();
    Color4(const uint8_t red, const uint8_t green,
            const uint8_t blue, const uint8_t alpha);
    ~Color4();

    uint32_t color() const { return RgbaToInt((int)m_r, (int)m_g, (int)m_b, (int)m_a); }
    uint8_t red() const { return m_r; }
    uint8_t green() const { return m_g; }
    uint8_t blue() const { return m_b; }
    uint8_t alpha() const { return m_a; }

    void reset();
};

}

#endif // COLOR4_H

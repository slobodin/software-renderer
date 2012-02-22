#ifndef RASTERIZER_H
#define RASTERIZER_H

#include "comm_pch.h"

#include "mesh.h"
#include "camera.h"

namespace rend
{

class Rasterizer
{
public:
    Rasterizer();

    void draw(const SPTR(Mesh) mesh, const SPTR(Camera) cam);
};

}

#endif // RASTERIZER_H

/*
 * softwarerenderer.h
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#ifndef SOFTWARERENDERER_H
#define SOFTWARERENDERER_H

#include "comm_pch.h"
#include "abstractrenderer.h"

namespace rend
{

class RenderList;
class Viewport;
class FrameBuffer;
class WireframeTriangleRasterizer;
class FlatTriangleRasterizer;

class SoftwareRenderer : public AbstractRenderer
{
    FrameBuffer *m_fb;
    WireframeTriangleRasterizer *m_wire;
    FlatTriangleRasterizer *m_flat;

public:
    SoftwareRenderer(int width, int height);
    ~SoftwareRenderer();

    virtual void render(const RenderList &rendlist);

    virtual void beginFrame(sptr(Viewport) viewport);
    virtual void endFrame(sptr(Viewport) viewport);

    virtual void resize(int w, int h);
};

}

#endif // SOFTWARERENDERER_H

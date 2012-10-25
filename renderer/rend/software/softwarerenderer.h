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
class GouraudTriangleRasterizer;
class TexturedTriangleRasterizer;

class SoftwareRenderer : public AbstractRenderer
{
    FrameBuffer *m_fb;

    // rasterizers collection
    WireframeTriangleRasterizer     *m_wire;
    FlatTriangleRasterizer          *m_flat;
    GouraudTriangleRasterizer       *m_gouraud;
    TexturedTriangleRasterizer      *m_text;

public:
    SoftwareRenderer(int width, int height);
    ~SoftwareRenderer();

    virtual void renderWorld(const RenderList &rendlist);
    virtual void renderGui(const list<sptr(GuiObject)> &guiObjects);

    virtual void beginFrame(sptr(Viewport) viewport);
    virtual void endFrame(sptr(Viewport) viewport);

    virtual void resize(int w, int h);

    virtual void setWorldViewMatrix(const math::M44 &m);
    virtual void setProjectionMatrix(const math::M44 &m);
};

}

#endif // SOFTWARERENDERER_H

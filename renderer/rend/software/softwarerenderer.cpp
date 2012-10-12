/*
 * softwarerenderer.cpp
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#include "softwarerenderer.h"

#include "viewport.h"
#include "renderlist.h"
#include "framebuffer.h"
#include "guiobject.h"
#include "texture.h"
#include "wireframetrianglerasterizer.h"
#include "flattrianglerasterizer.h"
#include "gouraudtrianglerasterizer.h"
#include "texturedtrianglerasterizer.h"

namespace rend
{

SoftwareRenderer::SoftwareRenderer(int width, int height)
    : m_fb(new FrameBuffer(width, height)),
      m_wire(new WireframeTriangleRasterizer()),
      m_flat(new FlatTriangleRasterizer()),
      m_gouraud(new GouraudTriangleRasterizer()),
      m_text(new TexturedTriangleRasterizer())
{
}

SoftwareRenderer::~SoftwareRenderer()
{
    if (m_fb)
        delete m_fb;
    if (m_wire)
        delete m_wire;
    if (m_flat)
        delete m_flat;
    if (m_gouraud)
        delete m_gouraud;
    if (m_text)
        delete m_text;
}

void SoftwareRenderer::renderWorld(const RenderList &rendlist)
{
    auto &trias = rendlist.triangles();
    TriangleRasterizer *rasterizer = 0;

    // painter's algorithm
    BOOST_REVERSE_FOREACH(const math::Triangle &t, trias)
    {
        if (!t.getMaterial())
        {
            syslog << "Material has not been setted for this triangle" << logdebug;
            continue;
        }

        switch(t.getMaterial()->shadeMode)
        {
        case Material::SM_WIRE:
            rasterizer = m_wire;
            break;

        case Material::SM_PLAIN_COLOR:
        case Material::SM_FLAT:
            rasterizer = m_flat;

        case Material::SM_GOURAUD:
            rasterizer = m_gouraud;
            break;

        case Material::SM_TEXTURE:
            rasterizer = m_text;
            break;

        default:
            syslog << "Unsupported shading mode." << logdebug;
            break;
        }

        if (rasterizer)
            rasterizer->drawTriangle(t, m_fb);
    }
}

void SoftwareRenderer::renderGui(const list<sptr(GuiObject)> &guiObjects)
{
    for (auto &obj : guiObjects)
    {
        auto texture = obj->getTexture();
        int xorig = obj->getPosition().x;
        int yorig = obj->getPosition().y;

        for (int y = 0; y < texture->height(); y++)
            for (int x = 0; x < texture->width(); x++)
            {
                m_fb->wpixel(x + xorig, y + yorig, texture->at(x, y));
            }
    }
}

void SoftwareRenderer::beginFrame(sptr(Viewport) /*viewport*/)
{
    m_fb->clear();
}

void SoftwareRenderer::endFrame(sptr(Viewport) viewport)
{
    viewport->flush(*m_fb);
}

void SoftwareRenderer::resize(int w, int h)
{
    m_fb->resize(w, h);
}

}

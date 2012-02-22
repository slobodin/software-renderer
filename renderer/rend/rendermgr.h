#ifndef RENDERMGR_H
#define RENDERMGR_H

#include "comm_pch.h"

#include "singleton.h"
#include "camera.h"
#include "rasterizer.h"
#include "resourcemgr.h"
#include "mesh.h"
#include "ospath.h"

namespace rend
{

class RenderMgr : public common::Singleton<RenderMgr>
{
    NONCOPYABLE(RenderMgr)

    SPTR(rend::Rasterizer) m_rasterizer;
    SPTR(Camera) m_camera;
    APTR(base::ResourceMgr) m_resourceMgr;

    vector<SPTR(rend::Mesh) > m_meshes;

public:
    RenderMgr(const int width, const int height);
    ~RenderMgr();

    void update();

    void addRenderable(const base::OsPath &path);
};

}

#endif // RENDERMGR_H

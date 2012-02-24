#ifndef RENDERMGR_H
#define RENDERMGR_H

#include "comm_pch.h"

#include "camera.h"
#include "rasterizer.h"
#include "mesh.h"
#include "ospath.h"

namespace rend
{

class RenderMgr
{
    NONCOPYABLE(RenderMgr)

    SPTR(rend::Rasterizer) m_rasterizer;
    string m_tkCanvasName;
    SPTR(Camera) m_camera;

    vector<SPTR(rend::Mesh) > m_meshes;

public:
    RenderMgr(const SPTR(Camera) cam);
    ~RenderMgr();

    void renderTo(const string &tkCanvas);
    void update();

    void addMesh(SPTR(rend::Mesh) mesh);

private:
    typedef vector<SPTR(rend::Mesh) >::iterator MeshIterator;
};

}

#endif // RENDERMGR_H

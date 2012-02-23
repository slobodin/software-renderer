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
    SPTR(Camera) m_camera;

    vector<SPTR(rend::Mesh) > m_meshes;

public:
    RenderMgr(const int width, const int height);
    ~RenderMgr();

    void update();
    // test func
    void rotate(const double dx, const double dy);

    void addMesh(SPTR(rend::Mesh) mesh);

private:
    typedef vector<SPTR(rend::Mesh) >::iterator MeshIterator;
};

}

#endif // RENDERMGR_H

#ifndef RENDERMGR_H
#define RENDERMGR_H

#include "comm_pch.h"

#include "camera.h"
#include "rasterizer.h"
#include "mesh.h"
#include "ospath.h"
#include "light.h"

namespace rend
{

class RenderMgr
{
    NONCOPYABLE(RenderMgr)

    SPTR(Rasterizer) m_rasterizer;
    string m_tkCanvasName;
    SPTR(Camera) m_camera;

    vector<SPTR(Mesh) > m_meshes;
    vector<SPTR(Light) > m_lights;

public:
    RenderMgr(const SPTR(Camera) cam);
    ~RenderMgr();

    void renderTo(const string &tkCanvas);
    void update();

    void addMesh(SPTR(rend::Mesh) mesh);
    void addLight(const Light::LightType &type,
                  const math::vec3 pos,
                  const math::vec3 &dir);

private:
    typedef vector<SPTR(rend::Mesh) >::iterator MeshIterator;
};

}

#endif // RENDERMGR_H

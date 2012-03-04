#ifndef RENDERMGR_H
#define RENDERMGR_H

#include "comm_pch.h"

#include "camera.h"
#include "rasterizer.h"
#include "mesh.h"
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

    // helpers
    void makeLight();

public:
    RenderMgr(const SPTR(Camera) cam);
    ~RenderMgr();

    void renderTo(const string &tkCanvas);
    void update();

    void addMesh(SPTR(rend::Mesh) mesh);
    void addAmbientLight(Color3 intensity);
    void addDirectionalLight(Color3 intensity, math::vec3 direction);

    void resize(int w, int h);

private:
    typedef vector<SPTR(Mesh) >::iterator MeshIterator;
    typedef vector<SPTR(Mesh) >::const_iterator MeshIterator_Const;
    typedef vector<SPTR(Light) >::iterator LightIterator;
    typedef vector<SPTR(Light) >::const_iterator LightIterator_Const;
};

}

#endif // RENDERMGR_H

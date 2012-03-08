#ifndef RENDERMGR_H
#define RENDERMGR_H

#include "comm_pch.h"

#include "camera.h"
#include "rasterizer.h"
#include "mesh.h"
#include "light.h"

namespace rend
{

class RenderMgr : boost::noncopyable
{
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
    SPTR(DirectionalLight) addDirectionalLight(Color3 intensity, math::vec3 direction);

    void resize(int w, int h);
};

}

#endif // RENDERMGR_H

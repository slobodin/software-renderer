/*
 * controller.cpp
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#include "controller.h"

#include "vec3.h"
#include "config.h"
#include "rendermgr.h"
#include "resourcemgr.h"
#include "viewport.h"
#include "camera.h"
#include "sceneobject.h"


#ifdef __linux__
#include <tcl8.5/tk.h>
#include <tcl8.5/tcl.h>
#include <GL/gl.h>
#include <GL/glx.h>
#elif WIN32
#include <tcl8.5/tk.h>
#include <tcl8.5/tcl.h>
#endif
#include <cpptk-1.0.2/cpptk.h>
#include <cpptk-1.0.2/base/cpptkbase.h>

namespace base
{

void Controller::resize(int w, int h)
{
    if (m_rendmgr)
        m_rendmgr->resize(w, h);
}

void Controller::test()
{

//    Display *display = XOpenDisplay(getenv("DISPLAY"));
//    Window m_xWindowId;

//    string windowId = Tk::winfo(Tk::id, ".c");
//    stringstream ss(windowId);
//    ss >> std::hex >> m_xWindowId;
////    m_xWindowId = windowId;

//    XWindowAttributes wndAttrib;
//    XGetWindowAttributes(display, m_xWindowId, &wndAttrib);

//    int a;
//    a = 5;
}

Controller::Controller(int argc, const char *argv[])
    : m_resourceMgr(new ResourceMgr),
      m_controllerConfig(0)
{
    // load config file
    string workingDir = argc > 1 ? argv[1] : "";
    m_controllerConfig = new Config(workingDir);

    // get cam position from the file (or set default)
    math::vec3 camPosition = m_controllerConfig->getRendererConfig().camPosition;
    syslog << "Initial camera position :" << camPosition << logmess;

    // create main camera
    m_mainCam = make_shared<rend::Camera>(camPosition);

    // notify rmgr about resource path. Thus it will can load resources from this path
    string resourcesPath = m_controllerConfig->getRendererConfig().pathToTheAssets;
    m_resourceMgr->addPath(resourcesPath);

    // load all loadable from assets path
    m_resourceMgr->loadAllResources();
}

Controller::~Controller()
{
    if (m_controllerConfig)
        delete m_controllerConfig;
}

void Controller::update()
{
    if (!m_rendmgr || !m_mainCam || !m_viewport)
    {
        syslog << "Controller uninitialized" << logerr;
        return;
    }

    // m_inputManager->capture() ???
    m_rendmgr->update();
}

std::pair<int, int> Controller::getViewportSize()
{
    return std::make_pair(m_controllerConfig->getRendererConfig().width,
                          m_controllerConfig->getRendererConfig().height);
}

void Controller::createRenderManager()
{
    string rendererMode = m_controllerConfig->getRendererConfig().rendererMode;

    if (rendererMode == "software")
        m_rendmgr = make_shared<rend::RenderMgr>(m_mainCam, m_viewport, rend::RM_SOFTWARE);
    else if (rendererMode == "opengl")
        m_rendmgr = make_shared<rend::RenderMgr>(m_mainCam, m_viewport, rend::RM_OPENGL);
    else
        throw ControllerException(string(string("Invalid renderer ") + rendererMode).c_str());

    // now add to the scene all scene objects, getted from the config file
    const SceneConfig &scCfg = m_controllerConfig->getSceneConfig();

    for (auto &objInfo : scCfg.objects)
    {
        auto obj = m_resourceMgr->getObject<rend::SceneObject>(objInfo.pathToTheModel);
        if (obj)
        {
            obj->setPosition(objInfo.position);
            obj->setScale(objInfo.scale);

            m_rendmgr->addSceneObject(obj);
        }
    }

    if (scCfg.dirLights.empty() && scCfg.ambIntensity.isBlack())
    {
        syslog << "No lights setted in scene config." << logwarn;
//        m_rendmgr->addAmbientLight(rend::Color3(255, 255, 255));
        return;
    }

    if (!scCfg.ambIntensity.isBlack())
        m_rendmgr->addAmbientLight(scCfg.ambIntensity);

    // add directional lights
    for (auto &dirLightInfo : scCfg.dirLights)
        m_rendmgr->addDirectionalLight(dirLightInfo.intensity, dirLightInfo.direction);

    // add point lights
    for (auto &ptLightInfo : scCfg.pointLights)
        m_rendmgr->addPointLight(ptLightInfo.intensity, ptLightInfo.position,
                                 ptLightInfo.kc, ptLightInfo.kl, ptLightInfo.kq);
}

bool Controller::viewportExist()
{
    if (m_viewport)
    {
        syslog << "Viewport already setted" << logwarn;
        return true;
    }

    return false;
}

sptr(rend::Camera) Controller::getCamera()
{
    return m_mainCam;
}

sptr(ResourceMgr) Controller::getResmgr()
{
    return m_resourceMgr;
}

sptr(rend::RenderMgr) Controller::getRendmgr()
{
    return m_rendmgr;
}

sptr(rend::Viewport) Controller::getViewport()
{
    return m_viewport;
}

}

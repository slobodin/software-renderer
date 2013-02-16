/*
 * controller.cpp
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#include "stdafx.h"

#include "controller.h"

#include "vec3.h"
#include "config.h"
#include "rendermgr.h"
#include "resourcemgr.h"
#include "viewport.h"
#include "camera.h"
#include "sceneobject.h"

namespace base
{

void Controller::resize(int w, int h)
{
    if (m_rendmgr)
        m_rendmgr->resize(w, h);
}

Controller::Controller(int argc, const char *argv[])
    : m_resourceMgr(new ResourceMgr),
      m_controllerConfig(0)
{
    // load config file
    std::string workingDir = argc > 1 ? argv[1] : "";
    m_controllerConfig = new Config(workingDir);

    // get cam position from the file (or set default)
    math::vec3 camPosition = m_controllerConfig->getRendererConfig().camPosition;
    syslog << "Initial camera position :" << camPosition << logmess;

    // create main camera
    m_mainCam = std::make_shared<rend::Camera>(camPosition);

    // notify rmgr about resource path. Thus it will can load resources from this path
    std::string resourcesPath = m_controllerConfig->getRendererConfig().pathToTheAssets;
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
    m_rendmgr->runFrame();
}

std::pair<int, int> Controller::getViewportSize()
{
    return std::make_pair(m_controllerConfig->getRendererConfig().width,
                          m_controllerConfig->getRendererConfig().height);
}

void Controller::createRenderManager()
{
    std::string rendererMode = m_controllerConfig->getRendererConfig().rendererMode;

    if (rendererMode == "software")
        m_rendmgr = std::make_shared<rend::RenderMgr>(m_mainCam, m_viewport, rend::RM_SOFTWARE);
    else if (rendererMode == "opengl")
        m_rendmgr = std::make_shared<rend::RenderMgr>(m_mainCam, m_viewport, rend::RM_OPENGL);
    else
        throw ControllerException(std::string(std::string("Invalid renderer ") + rendererMode).c_str());

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

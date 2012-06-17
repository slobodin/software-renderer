/*
 * controller.h
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "comm_pch.h"

namespace rend
{
class RenderMgr;
class Viewport;
class Camera;
}

namespace platform
{
class BaseApp;
}

namespace base
{

class ResourceMgr;

DECLARE_EXCEPTION(ControllerException)

class Controller : boost::noncopyable
{
    friend class platform::BaseApp;

    sptr(rend::RenderMgr)       m_rendmgr;
    sptr(rend::Viewport)        m_viewport;
    sptr(rend::Camera)          m_mainCam;
    sptr(ResourceMgr)           m_resourceMgr;

    void update();

public:
    Controller(const char *argv[]);
    virtual ~Controller();

    void setViewport(sptr(rend::Viewport) viewport);

    sptr(rend::Camera)      getCamera();
    sptr(ResourceMgr)       getResmgr();
    sptr(rend::RenderMgr)   getRendmgr();

    void resize(int w, int h);
};

}

#endif // CONTROLLER_H

/*
 * controller.h
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "comm_pch.h"
#include "dll.h"

#include "singleton.h"
#include "rendermgr.h"
#include "resourcemgr.h"

namespace base
{

DECLARE_EXCEPTION(ControllerException)

class DLL_PUBLIC Controller : public common::Singleton<Controller>, boost::noncopyable
{
    friend class Config;

protected:
    sptr(rend::RenderMgr) m_rendmgr;
    sptr(rend::Camera) m_mainCam;
    sptr(ResourceMgr) m_resourceMgr;

    string m_updateCallback;
    static void update();

    void resize(int w, int h);

    Controller(char *argv[], const string &conf);
    virtual ~Controller();

public:

    /*
    virtual void onKeyboardKeyPressed() = 0;
    virtual void onKeyboardKeyReleased() = 0;
    virtual void onMouseMotion() = 0;
    virtual void onMouseButtonPressed() = 0;
    virtual void onMouseButtonRelease() = 0;
    */

    void run();
};

}

#endif // CONTROLLER_H

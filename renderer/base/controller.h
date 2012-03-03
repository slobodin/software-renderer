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

class DLL_PUBLIC Controller : public common::Singleton<Controller>
{
    friend class Config;

    NONCOPYABLE(Controller)

protected:
    SPTR(rend::RenderMgr) m_rendmgr;
    SPTR(rend::Camera) m_mainCam;
    SPTR(ResourceMgr) m_resourceMgr;

    string m_updateCallback;
    static void update();

    void resize(int w, int h);

public:
    Controller(char *argv[], const string &conf);
    virtual ~Controller();

    void run();
};

}

#endif // CONTROLLER_H

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "comm_pch.h"
#include "dll.h"

#include "singleton.h"
#include "rendermgr.h"

namespace base
{

DECLARE_EXCEPTION(ControllerException)

class DLL_PUBLIC Controller : public common::Singleton<Controller>
{
    APTR(rend::RenderMgr) m_rendmgr;

    string m_modelName; // test

public:
    Controller(const string &conf);
};

}

#endif // CONTROLLER_H

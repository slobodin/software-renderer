/*
 * baseapp.cpp
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#include "baseapp.h"

#include "controller.h"

namespace platform
{

BaseApp::BaseApp()
{
}

BaseApp::~BaseApp()
{
}

int BaseApp::run()
{
    if (!m_clientController)
    {
        syslog << "Renderer controller not initialized. Can't work now." << logerr;
        return -1;
    }

    onFrameStart();

    m_clientController->update();

    onFrameEnd();

    return 0;
}


}

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
        return -1;

    onFrameStart();

    m_clientController->update();

    onFrameEnd();

    return 0;
}


}

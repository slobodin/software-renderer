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

    static long prevTime, currTime;

    timeval tm;
    gettimeofday(&tm, 0);
    currTime = tm.tv_sec * 1000 + tm.tv_usec / 1000;

    onFrameStart();

    m_clientController->update();
    update(currTime - prevTime);       // update user callback

    prevTime = currTime;

    onFrameEnd();

    return 0;
}


}

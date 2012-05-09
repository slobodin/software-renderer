/*
 * clientcontroller.h
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#ifndef CLIENTCONTROLLER_H
#define CLIENTCONTROLLER_H

#include "dll.h"

#include <memory>
#include "controller.h"
#include "logger.h"
#include "renderdevice.h"

//! Tk controller.
class ClientController : public base::Controller
{
    static void onMouseMotion(int x, int y);
    static void onMousePress(int x, int y);
    static void onMouseRelease(int x, int y);
    static void onKeyW();
    static void onKeyA();
    static void onKeyS();
    static void onKeyD();
    static void exit();

    int m_prevMouseX, m_prevMouseY;
    sptr(rend::RenderDevice) m_rendDevice;
    string m_updateCallback;
    static ClientController *m_this;

    void printCam();
    static void TkUpdate();

public:
    ClientController(char *argv[], const string &conf);

    void run();
};

#endif // CLIENTCONTROLLER_H

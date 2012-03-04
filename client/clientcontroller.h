#ifndef CLIENTCONTROLLER_H
#define CLIENTCONTROLLER_H

#include "dll.h"

#include <memory>
#include "controller.h"
#include "logger.h"

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

    void printCam();

public:
    ClientController(char *argv[], const string &conf);
};

#endif // CLIENTCONTROLLER_H

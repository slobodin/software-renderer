/*
 * application.h
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#ifndef APPLICATION_H
#define APPLICATION_H

#include "clientcontroller.h"

class Application
{
    std::auto_ptr<ClientController> m_controller;
public:
    Application(int , char *argv[]);

    void run();
};

#endif // APPLICATION_H

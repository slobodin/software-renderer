#ifndef APPLICATION_H
#define APPLICATION_H

#define CLIENT_MAIN
#include "dll.h"

#include <memory>
#include "controller.h"
#include "logger.h"

using namespace base;

class Application
{
    std::auto_ptr<Controller> m_controller;
public:
    Application();
};

#endif // APPLICATION_H

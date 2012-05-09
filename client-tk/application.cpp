/*
 * application.cpp
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#include "application.h"

Application::Application(int , char *argv[])
    : m_controller(new ClientController(argv, "../resources/conf.yaml"))
{
}

void Application::run()
{
    m_controller->run();
}

int main(int argc, char *argv[])
try
{
    Application app(argc, argv);

    app.run();

    return 0;
}
catch(common::Exception &e)
{
    *syslog << "Renderer exception:" << e.what() << logerr;
    return 1;
}
catch (std::exception &e)
{
    *syslog << "stl exception:" << e.what() << logerr;
    return 1;
}
catch(...)
{
    *syslog << "Unknown exception occurred" << logerr;
    return 1;
}

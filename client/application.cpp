#include "application.h"

Application::Application(int , char *argv[])
    : m_controller(new ClientController(argv, "conf.yaml"))
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

    return 1;
}
catch (std::exception &e)
{

    return 1;
}
catch(...)
{
    return 1;
}

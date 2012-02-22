#include "application.h"

Application::Application()
    : m_controller(new Controller("conf.yaml"))
{
}

int main()
try
{
    Application app;

    return 0;
}
catch(...)
{

    return 1;
}

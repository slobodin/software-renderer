/*
 * main.cpp
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#include "windowsapplication.h"

int main(int argc, const char **argv) try
{
    WindowsApplication app(argc, argv);

    return app.run();
}
catch (common::Exception &e)
{
    std::cerr << "Program terminated with exception " << e.what() << "\n";
}
catch (...)
{
    std::cerr << "Something wrong. Aborting.\n";
}

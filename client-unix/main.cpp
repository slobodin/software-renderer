/*
 * main.cpp
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#include "unixapplication.h"

int main(int argc, const char **argv)
try
{
    UnixApplication app(argc, argv);

    return app.run();
}
catch (common::Exception &e)
{
    std::cerr << "Renderer exception: " << e.what() << "\n";
    return 1;
}
catch (...)
{
    std::cerr << "Unknown exception occurred. Aborting.\n";
    return 1;
}

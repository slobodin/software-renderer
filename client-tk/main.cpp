/*
 * main.cpp
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#include "tkapplication.h"

int main(int argc, const char **argv)
try
{
//    Application app(argc, argv);

//    return app.run();
    return 0;
}
catch (common::Exception &e)
{
    std::cerr << "Renderer exception: " << e.what() << "\n";
    return 1;
}
catch (std::exception &e)
{
    std::cerr << "std exception: " << e.what() << "\n";
    return 1;
}
catch (...)
{
    std::cerr << "Unknown exception occurred. Aborting.\n";
    return 1;
}


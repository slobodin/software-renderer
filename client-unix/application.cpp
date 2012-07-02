/*
 * application.cpp
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#include "application.h"

Application::Application(int argc, const char *argv[])
    : platform::BaseAppLinux(argc, argv)
{
    m_playerCamera = m_clientController->getCamera();
}

Application::~Application()
{
}

void Application::onFrameStart()
{
}

void Application::onFrameEnd()
{
}

void Application::onMouseEvent(const platform::MouseEvent &ev)
{
//    if (ev.isLeftPressed())
//        std::cerr << "Left pressed\n";
//    if (ev.isRightPressed())
//        std::cerr << "Right pressed\n";
//    if (ev.isMiddlePressed())
//        std::cerr << "Middle pressed\n";

//    std::cerr << "x: " << ev.x << " y: " << ev.y << "\n";
}

void Application::onKeyPressed(const platform::KeyboardEvent &ev)
{
//    if (ev.keycode() == platform::KEY_NONE)
//        std::cerr << "Key none!\n";

//    std::cerr << "Getted keycode: " << std::hex << ev.keycode() << std::dec << "\n";
}

void Application::onKeyReleased(const platform::KeyboardEvent &ev)
{
//    if (ev.keycode() == platform::KEY_NONE)
//        std::cerr << "Key none!\n";

//    std::cerr << "Getted keycode: " << std::hex << ev.keycode() << "\n";
}

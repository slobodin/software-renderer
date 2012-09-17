/*
 * application.cpp
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#include "application.h"

void Application::setWindowTitle(const string &title)
{
    const char *title_c = title.c_str();
    Display* d = m_viewport->getXDisplay();

    XTextProperty tp;
    tp.value = (unsigned char *)title_c;
    tp.encoding = XA_WM_NAME;
    tp.format = 8;
    tp.nitems = strlen(title_c);

    XSetWMName(d, m_viewport->getWindow(), &tp);
    XStoreName(d, m_viewport->getWindow(), title_c);
    XSetWMIconName(d, m_viewport->getWindow(), &tp);
    XSetIconName(d, m_viewport->getWindow(), title_c);
}

Application::Application(int argc, const char *argv[])
    : platform::BaseAppLinux(argc, argv)
{
    m_playerCamera = m_clientController->getCamera();

    // set window title
    setWindowTitle("Nyan");

    auto tank = m_clientController->getResmgr()->getObject<rend::SceneObject>("tank1.plg");
    auto tower = m_clientController->getResmgr()->getObject<rend::SceneObject>("tower1.plg");
    auto cube = m_clientController->getResmgr()->getObject<rend::SceneObject>("cube1.plg");

    m_clientController->getRendmgr()->addSceneObject(tank);
    m_clientController->getRendmgr()->addSceneObject(cube);
    m_clientController->getRendmgr()->addSceneObject(tower);
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
    static platform::MouseEvent prevEvent = ev;
    static int yaw, pitch;

    int dx = ev.x - prevEvent.x;
    int dy = ev.y - prevEvent.y;

    if (ev.isLeftPressed())
    {
        yaw += dx;
        pitch += dy;

        if (abs(yaw) > 360) yaw %= 360;
        if (abs(pitch) > 360) pitch %= 360;

//        m_playerCamera->setEulerAnglesRotation(yaw, pitch, 0);

        math::M33 rotM = math::M33::getRotateYawPitchRollMatrix(yaw, pitch, 0);
        math::vec3 camDir = math::vec3(0, 0, 1) * rotM;
//        m_playerCamera->setDirection(camDir);
        m_playerCamera->setEulerAnglesRotation(yaw, pitch, 0);
    }

    prevEvent = ev;

//    if (ev.isLeftPressed())
//        std::cerr << "Left pressed\n";
//    if (ev.isRightPressed())
//        std::cerr << "Right pressed\n";
//    if (ev.isMiddlePressed())
//        std::cerr << "Middle pressed\n";

    std::cerr << "y: " << yaw << " p: " << pitch << "\n";
}

void Application::onKeyPressed(const platform::KeyboardEvent &ev)
{
    static const double velocity = 10.0;
    static math::vec3 ds;
    static math::vec3 position;

    ds.zero();
    position = m_playerCamera->getPosition();

    if (ev.keycode() == platform::KEY_UP)
    {
        ds = m_playerCamera->getDirection() * velocity;
        position += ds;
    }
    else if (ev.keycode() == platform::KEY_DOWN)
    {
        ds = m_playerCamera->getDirection() * velocity;
        position -= ds;
    }
    else if (ev.keycode() == platform::KEY_RIGHT)
    {
        ds = m_playerCamera->getRightVector() * velocity;
        position += ds;
    }
    else if (ev.keycode() == platform::KEY_LEFT)
    {
        ds = m_playerCamera->getRightVector() * velocity;
        position -= ds;
    }
    else
        return;

    m_playerCamera->setPosition(position);
}

void Application::onKeyReleased(const platform::KeyboardEvent &ev)
{
}

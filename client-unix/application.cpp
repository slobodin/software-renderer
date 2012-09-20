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

void Application::update(float dt)
{
    static int yaw, roll;

    yaw += 1;
    roll += 1;
    if (abs(yaw) > 360) yaw %= 360;
    if (abs(roll) > 360) roll %= 360;

    // hammer
    math::vec3 transl = m_hammer->getPosition();

    m_hammer->resetTransformation();

    math::M33 rotM = math::M33::getRotateYawPitchRollMatrix(yaw, 0, 0);
    math::M33 scaleM = math::M33::getScaleMatrix(math::vec3(15.0, 15.0, 15.0));

    m_hammer->setTransformation(math::M44(rotM * scaleM, transl));

    // sphere
    transl = m_sphere->getPosition();

    m_sphere->resetTransformation();

    rotM = math::M33::getRotateYawPitchRollMatrix(0, 0, roll);
    scaleM = math::M33::getScaleMatrix(math::vec3(15.0, 15.0, 15.0));

    m_sphere->setTransformation(math::M44(rotM * scaleM, transl));
}

Application::Application(int argc, const char *argv[])
    : platform::BaseAppLinux(argc, argv)
{
    m_playerCamera = m_clientController->getCamera();

    // set window title
    setWindowTitle("Nyan");

    sptr(base::ResourceMgr) rmgr = m_clientController->getResmgr();
    sptr(rend::RenderMgr) rendmgr = m_clientController->getRendmgr();

    /*auto tank = rmgr->getObject<rend::SceneObject>("tank1.plg");
    auto clonedTank = tank->clone();
    clonedTank->setPosition(math::vec3(0, 500, 0));
    m_clientController->getRendmgr()->addSceneObject(clonedTank);

    auto tower = rendmgr->getSceneObject("tower");
    auto clonedTower = tower->clone();
    clonedTower->setPosition(math::vec3(0, 500, -250));
    m_clientController->getRendmgr()->addSceneObject(clonedTower);*/

    m_sphere = rendmgr->getSceneObject("Sphere");
    m_sphere->setScale(math::vec3(15.0, 15.0, 15.0));

    m_hammer = rendmgr->getSceneObject("Hammer");
    m_hammer->setScale(math::vec3(15.0, 15.0, 15.0));

    auto tie = rendmgr->getSceneObject("TIEFIGTH");

    tie->setRotation(math::vec3(-90.0, 0.0, 0.0));
    tie->setScale(math::vec3(15.0, 15.0, 15.0));
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

        m_playerCamera->setEulerAnglesRotation(yaw, pitch, 0);
    }

    prevEvent = ev;
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

void Application::onKeyReleased(const platform::KeyboardEvent &/*ev*/)
{
}

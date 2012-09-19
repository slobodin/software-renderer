/*
 * tkapplication.cpp
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#include "tkapplication.h"

TkApplication::TkApplication(int argc, const char *argv[])
    : platform::BaseAppTk(argc, argv)
{
    m_playerCamera = m_clientController->getCamera();

    sptr(base::ResourceMgr) rmgr = m_clientController->getResmgr();
    sptr(rend::RenderMgr) rendmgr = m_clientController->getRendmgr();

    rendmgr->addDirectionalLight(rend::Color3(255, 100, 50), math::vec3(0, 1, 0));
//    rendmgr->addAmbientLight(rend::Color3(255 * 0.3, 255 * 0.3, 255 * 0.3));

    /*auto tank = rmgr->getObject<rend::SceneObject>("tank1.plg");
    auto clonedTank = tank->clone();
    clonedTank->setPosition(math::vec3(0, 500, 0));
    m_clientController->getRendmgr()->addSceneObject(clonedTank);

    auto tower = rendmgr->getSceneObject("tower");
    auto clonedTower = tower->clone();
    clonedTower->setPosition(math::vec3(0, 500, -250));
    m_clientController->getRendmgr()->addSceneObject(clonedTower);*/

    auto sphere = rendmgr->getSceneObject("Sphere");
    sphere->setScale(math::vec3(5.0, 5.0, 5.0));

    auto hammer = rendmgr->getSceneObject("Hammer");
    hammer->setScale(math::vec3(15.0, 15.0, 15.0));
}

TkApplication::~TkApplication()
{
}

void TkApplication::onFrameStart()
{
}

void TkApplication::onFrameEnd()
{
}

void TkApplication::onMouseEvent(const platform::MouseEvent &ev)
{
    static int yaw, pitch;

    if (ev.isLeftPressed())
    {
        yaw -= ev.x;            // inverted
        pitch -= ev.y;

        if (abs(yaw) > 360) yaw %= 360;
        if (abs(pitch) > 360) pitch %= 360;

        m_playerCamera->setEulerAnglesRotation(yaw, pitch, 0);
    }
}

void TkApplication::onKeyPressed(const platform::KeyboardEvent &ev)
{
    static const double velocity = 10.0;
    static math::vec3 ds;
    static math::vec3 position;

    ds.zero();
    position = m_playerCamera->getPosition();

    if (ev.keycode() == platform::KEY_KEY_W)
    {
        ds = m_playerCamera->getDirection() * velocity;
        position += ds;
    }
    else if (ev.keycode() == platform::KEY_KEY_S)
    {
        ds = m_playerCamera->getDirection() * velocity;
        position -= ds;
    }
    else if (ev.keycode() == platform::KEY_KEY_D)
    {
        ds = m_playerCamera->getRightVector() * velocity;
        position += ds;
    }
    else if (ev.keycode() == platform::KEY_KEY_A)
    {
        ds = m_playerCamera->getRightVector() * velocity;
        position -= ds;
    }
    else
        return;

    m_playerCamera->setPosition(position);
}

void TkApplication::onKeyReleased(const platform::KeyboardEvent &ev)
{
}

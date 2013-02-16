/*
 * winapplication.cpp
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#include "winapplication.h"

void WinApplication::update(float dt)
{

}

WinApplication::WinApplication(int argc, const char *argv[])
    : platform::BaseAppWin(argc, argv)
{
    m_playerCamera = m_clientController->getCamera();

    auto rmgr = m_clientController->getResmgr();
    auto rendmgr = m_clientController->getRendmgr();

    // create terrain
    auto heightMapTexture = rmgr->getObject<rend::Texture>("texture_water_track_height_03");
    auto texture = rmgr->getObject<rend::Texture>("texture_water_track_color_03");
    auto terrain = std::make_shared<rend::TerrainSceneObject>(3000.f, 3000.f, 600.f, heightMapTexture, texture);

    rendmgr->addSceneObject(terrain);

//    rendmgr->addGuiObject(std::make_shared<rend::GuiObject>(texture));

    auto teapot = rmgr->getObject<rend::SceneObject>("teapot.obj");
    if (teapot)
    {
        //teapot->setScale(math::vec3(50, 50, 50));
        teapot->getMesh()->setShadingMode(rend::Material::SM_GOURAUD);
    }
}

WinApplication::~WinApplication()
{
}

void WinApplication::onFrameStart()
{
}

void WinApplication::onFrameEnd()
{
}

void WinApplication::onMouseEvent(const platform::MouseEvent &ev)
{
    static int yaw, pitch;
    static int prevx, prevy;

    if (ev.isLeftPressed())
    {
        yaw -= prevx - ev.x;            // inverted
        pitch -= prevy - ev.y;

        if (abs(yaw) > 360) yaw %= 360;
        if (abs(pitch) > 360) pitch %= 360;

        m_playerCamera->setEulerAnglesRotation(yaw, pitch, 0.f);
    }

    prevx = ev.x;
    prevy = ev.y;
}

void WinApplication::onKeyPressed(const platform::KeyboardEvent &ev)
{
    static const float velocity = 100.f;
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

void WinApplication::onKeyReleased(const platform::KeyboardEvent &/*ev*/)
{
}

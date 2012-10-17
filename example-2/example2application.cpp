/*
 * example2application.cpp
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#include "example2application.h"

void Example2Application::update(float dt)
{
    static int yaw, roll;

    yaw += 1;
    roll += 1;
    if (abs(yaw) > 360) yaw %= 360;
    if (abs(roll) > 360) roll %= 360;

    sptr(rend::Light) ptL = m_clientController->getRendmgr()->getFirstPointLight();
    if (ptL)
    {
        auto transl = ptL->getPosition();
        auto rotM = math::M33::getRotateYawPitchRollMatrix(3, 0, 0);

        transl = transl * rotM;

        ptL->setPosition(transl);
    }

    if (m_fpsLabel)
    {
        double fps = dt / 1000;
        fps = 1.0 / fps;
        m_fpsLabel->setText(string("FPS:") + common::toString((int)fps));
    }
}

Example2Application::Example2Application(int argc, const char *argv[])
    : platform::BaseAppTk(argc, argv)
{
    m_playerCamera = m_clientController->getCamera();

    sptr(base::ResourceMgr) rmgr = m_clientController->getResmgr();
    sptr(rend::RenderMgr) rendmgr = m_clientController->getRendmgr();

    auto m_cube = rendmgr->getSceneObject("Cube");
    if (m_cube)
    {
        m_cube->setRotation(math::vec3(0.0, 45.0, 45.0));
        m_cube->setScale(math::vec3(45.0, 45.0, 45.0));
    }

    if (!m_cube)
        std::cerr << "Error: Missing some resources.\n";

    auto textureFont = rmgr->getObject<rend::Texture>("texture_TextureFont");
    if (textureFont)
    {
        m_fpsLabel = make_shared<rend::TextObject>(textureFont, 16, 16);
        rendmgr->addGuiObject(m_fpsLabel);
    }
}

void Example2Application::onMouseEvent(const platform::MouseEvent &ev)
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

void Example2Application::onKeyPressed(const platform::KeyboardEvent &ev)
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

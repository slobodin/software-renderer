/*
 * example1application.cpp
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#include "example1application.h"

void Example1Application::update(float dt)
{
    static int yaw, roll;

    yaw += 1;
    roll += 1;
    if (abs(yaw) > 360) yaw %= 360;
    if (abs(roll) > 360) roll %= 360;

    // hammer
    math::vec3 transl;
    math::M33 rotM, scaleM;

    if (m_hammer)
    {
        transl = m_hammer->getPosition();

        m_hammer->resetTransformation();

        rotM = math::M33::getRotateYawPitchRollMatrix(yaw, 0, 0);
        scaleM = math::M33::getScaleMatrix(math::vec3(15.0, 15.0, 15.0));

        m_hammer->setTransformation(math::M44(rotM * scaleM, transl));
    }

    // sphere
    if (m_sphere)
    {
        transl = m_sphere->getPosition();

        m_sphere->resetTransformation();

        rotM = math::M33::getRotateYawPitchRollMatrix(0, 0, roll);
        scaleM = math::M33::getScaleMatrix(math::vec3(15.0, 15.0, 15.0));

        m_sphere->setTransformation(math::M44(rotM * scaleM, transl));
    }

    sptr(rend::Light) ptL = m_clientController->getRendmgr()->getFirstPointLight();
    if (ptL)
    {
        transl = ptL->getPosition();
        rotM = math::M33::getRotateYawPitchRollMatrix(3, 0, 0);

        transl = transl * rotM;

        ptL->setPosition(transl);
        m_lightPoint->setPosition(transl);
    }

    if (m_fpsLabel)
    {
        double fps = dt / 1000;
        fps = 1.0 / fps;
        m_fpsLabel->setText(string("FPS:") + common::toString((int)fps));
    }
}

Example1Application::Example1Application(int argc, const char *argv[])
    : platform::BaseAppTk(argc, argv)
{
    m_playerCamera = m_clientController->getCamera();

    sptr(base::ResourceMgr) rmgr = m_clientController->getResmgr();
    sptr(rend::RenderMgr) rendmgr = m_clientController->getRendmgr();

    m_sphere = rendmgr->getSceneObject("Sphere");
    if (m_sphere)
    {
        m_sphere->setScale(math::vec3(15.0, 15.0, 15.0));

        m_lightPoint = m_sphere->clone();
        m_lightPoint->resetTransformation();
        m_lightPoint->getMesh()->setShadingMode(rend::Material::SM_WIRE);
        rendmgr->addSceneObject(m_lightPoint);
    }

    m_hammer = rendmgr->getSceneObject("Hammer");
    if (m_hammer)
    {
        m_hammer->setScale(math::vec3(15.0, 15.0, 15.0));
    }

    auto cube = rendmgr->getSceneObject("Cube");
    if (cube)
        cube->setScale(math::vec3(15.0, 15.0, 15.0));

    auto al = rendmgr->getSceneObject("al.obj");
    if (al)
        al->setScale(math::vec3(35.0, 35.0, 35.0));

    if (!al || !cube || !m_sphere || !m_hammer)
        std::cerr << "Error: Missing some resources.\n";

    auto textureFont = rmgr->getObject<rend::Texture>("texture_TextureFont");
    if (textureFont)
    {
        m_fpsLabel = make_shared<rend::TextObject>(textureFont, 16, 16);
        rendmgr->addGuiObject(m_fpsLabel);
    }
}

void Example1Application::onMouseEvent(const platform::MouseEvent &ev)
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

void Example1Application::onKeyPressed(const platform::KeyboardEvent &ev)
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

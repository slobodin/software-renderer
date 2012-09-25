/*
 * example3application.cpp
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#include "example3application.h"

void Example3Application::update(float dt)
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
        auto rotM = math::M33::getRotateYawPitchRollMatrix(0, 0, 3);

        transl = transl * rotM;

        ptL->setPosition(transl);
        if (m_sphere)
            m_sphere->setPosition(transl);
    }
}

Example3Application::Example3Application(int argc, const char *argv[])
    : platform::BaseAppTk(argc, argv)
{
    m_playerCamera = m_clientController->getCamera();

    sptr(base::ResourceMgr) rmgr = m_clientController->getResmgr();
    sptr(rend::RenderMgr) rendmgr = m_clientController->getRendmgr();

    // create terrain
    auto heightMapTexture = rmgr->getObject<rend::Texture>("texture_terrain2");
    auto terrain = boost::make_shared<rend::TerrainSceneObject>(4000, 4000, 700, heightMapTexture);

    rendmgr->addSceneObject(terrain);

    m_sphere = rendmgr->getSceneObject("Sphere");
    if (m_sphere)
        m_sphere->getMesh()->setShadingMode(rend::Material::SM_WIRE);
}

Example3Application::~Example3Application()
{
}

void Example3Application::onFrameStart()
{
}

void Example3Application::onFrameEnd()
{
}

void Example3Application::onMouseEvent(const platform::MouseEvent &ev)
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

void Example3Application::onKeyPressed(const platform::KeyboardEvent &ev)
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

void Example3Application::onKeyReleased(const platform::KeyboardEvent &ev)
{
}

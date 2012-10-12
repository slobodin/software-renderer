/*
 * tkapplication.cpp
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#include "tkapplication.h"

void TkApplication::update(float /*dt*/)
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
}

TkApplication::TkApplication(int argc, const char *argv[])
    : platform::BaseAppTk(argc, argv)
{
    m_playerCamera = m_clientController->getCamera();

    sptr(base::ResourceMgr) rmgr = m_clientController->getResmgr();
    sptr(rend::RenderMgr) rendmgr = m_clientController->getRendmgr();

    m_hammer = rendmgr->getSceneObject("Hammer");
    if (m_hammer)
    {
        m_hammer->setScale(math::vec3(15.0, 15.0, 15.0));
        m_hammer->getMesh()->setShadingMode(rend::Material::SM_GOURAUD);
    }

    // create terrain
    auto heightMapTexture = rmgr->getObject<rend::Texture>("texture_terrain2");
    auto texture = rmgr->getObject<rend::Texture>("texture_texture-terrain");
    auto terrain = boost::make_shared<rend::TerrainSceneObject>(3000, 3000, 500, heightMapTexture, texture);

    rendmgr->addSceneObject(terrain);
    rendmgr->addGuiObject(make_shared<rend::GuiObject>(texture));

    m_sphere = rendmgr->getSceneObject("Sphere");
    if (m_sphere)
    {
        m_sphere->setScale(math::vec3(15.0, 15.0, 15.0));
        m_sphere->getMesh()->setShadingMode(rend::Material::SM_GOURAUD);
    }
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

void TkApplication::onKeyReleased(const platform::KeyboardEvent &/*ev*/)
{
}

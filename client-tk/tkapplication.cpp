/*
 * tkapplication.cpp
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#include "tkapplication.h"

void TkApplication::showStats(float dt)
{
    auto frameStats = m_clientController->getRendmgr()->getLastFrameStats();
    m_debugStats1->setText(string("Triangles for rasterization:") + common::toString(frameStats.trianglesForRaster));
    m_debugStats2->setText(string("Triangles before culling:") + common::toString(frameStats.trianglesOnFrameStart));
    double fps = dt / 1000;
    fps = 1.0 / fps;
    m_debugStats3->setText(string("FPS:") + common::toString((int)fps));
}

void TkApplication::update(float dt)
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

    sptr(rend::Light) ptL = m_clientController->getRendmgr()->getFirstPointLight();
    if (ptL)
    {
        transl = ptL->getPosition();
        rotM = math::M33::getRotateYawPitchRollMatrix(3, 0, 0);

        transl = transl * rotM;

        ptL->setPosition(transl);
//        m_lightPoint->setPosition(transl);
    }

    showStats(dt);
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
        m_hammer->getMesh()->setShadingMode(rend::Material::SM_FLAT);
    }

    // create terrain
    auto heightMapTexture = rmgr->getObject<rend::Texture>("texture_terrain2");
    auto texture = rmgr->getObject<rend::Texture>("texture_texture-terrain");
    auto terrain = boost::make_shared<rend::TerrainSceneObject>(3000, 3000, 600, heightMapTexture, texture);

//    rendmgr->addSceneObject(terrain);
//    rendmgr->addGuiObject(make_shared<rend::GuiObject>(texture));

    m_sphere = rendmgr->getSceneObject("Sphere");
    if (m_sphere)
    {
        m_sphere->setScale(math::vec3(15.0, 15.0, 15.0));
        m_sphere->getMesh()->setShadingMode(rend::Material::SM_FLAT);
    }

    auto cube = rendmgr->getSceneObject("Cube");
    if (cube)
    {
        cube->setScale(math::vec3(35.0, 35.0, 35.0));
        auto texture = rmgr->getObject<rend::Texture>("texture_chessboard");
        cube->getMesh()->setTexture(texture);
    }

    auto statue = rendmgr->getSceneObject("statue2.obj");
    statue->setScale({5, 5, 5});

    auto textureFont = rmgr->getObject<rend::Texture>("texture_TextureFont");
    m_debugStats1 = make_shared<rend::TextObject>(textureFont, 16, 16);
    rendmgr->addGuiObject(m_debugStats1);
    m_debugStats2 = make_shared<rend::TextObject>(textureFont, 16, 16);
    m_debugStats2->setPosition({0, 16, 0});
    rendmgr->addGuiObject(m_debugStats2);
    m_debugStats3 = make_shared<rend::TextObject>(textureFont, 16, 16);
    m_debugStats3->setPosition({0, 32, 0});
    rendmgr->addGuiObject(m_debugStats3);
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

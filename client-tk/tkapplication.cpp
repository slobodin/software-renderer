/*
 * tkapplication.cpp
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#include "tkapplication.h"

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

    // sphere
    if (m_sphere)
    {
        transl = m_sphere->getPosition();

        m_sphere->resetTransformation();

        rotM = math::M33::getRotateYawPitchRollMatrix(0, 0, roll);
        scaleM = math::M33::getScaleMatrix(math::vec3(15.0, 15.0, 15.0));

        m_sphere->setTransformation(math::M44(rotM * scaleM, transl));
    }
}

TkApplication::TkApplication(int argc, const char *argv[])
    : platform::BaseAppTk(argc, argv)
{
    m_playerCamera = m_clientController->getCamera();

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
    if (m_sphere)
    {
        m_sphere->setScale(math::vec3(15.0, 15.0, 15.0));
    }

    m_hammer = rendmgr->getSceneObject("Hammer");
    if (m_hammer)
    {
        m_hammer->setScale(math::vec3(15.0, 15.0, 15.0));
    }


//    auto tie = rendmgr->getSceneObject("TIEFIGTH");
//    tie->setRotation(math::vec3(-90.0, 0.0, 0.0));
//    tie->setScale(math::vec3(15.0, 15.0, 15.0));

//    tie->getMesh()->setSideType(rend::Material::TWO_SIDE);

//    auto s = rendmgr->getSceneObject("Sphere,4");
//    s->setScale(math::vec3(35.0, 35.0, 35.0));

    auto cube = rendmgr->getSceneObject("Cube");
    cube->setScale(math::vec3(15.0, 15.0, 15.0));

/*    auto cessna = rendmgr->getSceneObject("cessna.obj");
    if (cessna)
        cessna->setScale(math::vec3(15.0, 15.0, 15.0));*/

    auto al = rendmgr->getSceneObject("al.obj");
    if (al)
        al->setScale(math::vec3(35.0, 35.0, 35.0));
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

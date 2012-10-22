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

void TkApplication::createTestTriangle()
{
    auto newMesh = make_shared<rend::Mesh>();
    rend::VertexBuffer vb;

    vb.setType(rend::VertexBuffer::INDEXEDTRIANGLELIST);

    math::vertex v1; v1.p = { -100, 600, -100 };
    math::vertex v2; v2.p = { -100, 0, -100 };
    math::vertex v3; v3.p = { 100, 0, -100 };

    vector<math::vertex> vertexList = { v1, v2, v3 };
    vector<int> indices = { 0, 1, 2 };

    vb.appendVertices(vertexList, indices);

    auto material = make_shared<rend::Material>();
    material->plainColor = rend::Color3(255, 255, 255);
    material->ambientColor = rend::Color3(255, 255, 255);
    material->diffuseColor = rend::Color3(255, 255, 255);
    material->shadeMode = rend::Material::SM_GOURAUD;
    material->sideType = rend::Material::TWO_SIDE;

    vb.setMaterial(material);
    newMesh->appendSubmesh(vb);

    auto newObject = make_shared<rend::SceneObject>(newMesh);
    m_clientController->getRendmgr()->addSceneObject(newObject);

    auto mesh2 = newMesh->clone();
    mesh2->setShadingMode(rend::Material::SM_WIRE);
    auto newObject2 = make_shared<rend::SceneObject>(mesh2);
    m_clientController->getRendmgr()->addSceneObject(newObject2);
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

//        ptL->setPosition(transl);
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

    // create terrain
    auto heightMapTexture = rmgr->getObject<rend::Texture>("texture_terrain2");
    auto texture = rmgr->getObject<rend::Texture>("texture_texture-terrain");
    auto terrain = boost::make_shared<rend::TerrainSceneObject>(3000, 3000, 600, heightMapTexture/*, texture*/);

    m_sphere = rendmgr->getSceneObject("Sphere");
    if (m_sphere)
        m_sphere->getMesh()->setShadingMode(rend::Material::SM_GOURAUD);

    rendmgr->addSceneObject(terrain);
//    rendmgr->addGuiObject(make_shared<rend::GuiObject>(texture));

    auto cube = rendmgr->getSceneObject("Cube");
    if (cube)
    {
//        auto texture = rmgr->getObject<rend::Texture>("texture_chessboard");
//        cube->getMesh()->setTexture(texture);
        cube->getMesh()->setShadingMode(rend::Material::SM_GOURAUD);
    }

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

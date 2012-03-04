#include "clientcontroller.h"

#include <third-party/cpptk-1.0.2/cpptk.h>
#include "light.h"

using namespace Tk;
using namespace base;
using namespace math;

void ClientController::onMouseMotion(int x, int y)
{
    static int yaw, pitch;
    ClientController *m_this = dynamic_cast<ClientController *>(ptr());

    int dx = m_this->m_prevMouseX - x;
    int dy = m_this->m_prevMouseY - y;
    yaw += dx;
    pitch += dy;
    if (abs(yaw) > 360) yaw %= 360;
    if (abs(pitch) > 360) pitch %= 360;
    m_this->m_mainCam->buildCamMatrix(yaw, pitch, 0);

    m_this->m_prevMouseX = x;
    m_this->m_prevMouseY = y;

    (".info_frame.camera" << Tk::configure()) -text(m_this->m_mainCam->state());
}

void ClientController::onMousePress(int x, int y)
{
    ClientController *m_this = dynamic_cast<ClientController *>(ptr());

    m_this->m_prevMouseX = x;
    m_this->m_prevMouseY = y;
}

void ClientController::onMouseRelease(int x, int y)
{
    ClientController *m_this = dynamic_cast<ClientController *>(ptr());

    m_this->m_prevMouseX = x;
    m_this->m_prevMouseY = y;
}

void ClientController::onKeyW()
{
    ClientController *m_this = dynamic_cast<ClientController *>(ptr());
    vec3 pos = m_this->m_mainCam->getPosition();
    vec3 dir = m_this->m_mainCam->getDirection();

    vec3 delta = 5 * dir;

    pos.x += 5*sin(dir.y);
    pos.z += 5*cos(dir.y);

//    pos += delta;
//    pos.z += 5;
    m_this->m_mainCam->setPosition(pos);

    (".info_frame.camera" << Tk::configure()) -text(m_this->m_mainCam->state());
}

void ClientController::onKeyA()
{
}

void ClientController::onKeyS()
{
    ClientController *m_this = dynamic_cast<ClientController *>(ptr());
    vec3 pos = m_this->m_mainCam->getPosition();
    vec3 dir = m_this->m_mainCam->getDirection();

    vec3 delta = 5 * dir;

    pos -= delta;
//    pos.z -= 5;
    m_this->m_mainCam->setPosition(pos);

    (".info_frame.camera" << Tk::configure()) -text(m_this->m_mainCam->state());
}

void ClientController::onKeyD()
{
}

void ClientController::exit()
{
    ::exit(0);
}

void ClientController::printCam()
{

}

ClientController::ClientController(char *argv[], const string &conf)
    : base::Controller(argv, conf),
      m_prevMouseX(0),
      m_prevMouseY(0)
{    
    // crete gui controls
    Tk::frame(".info_frame");

    Tk::label(".info_frame.camera") -Tk::width(80) -Tk::height(5)
            -anchor(nw) -justify(left);
    Tk::button(".info_frame.quit") -text("Quit") -command(&ClientController::exit);

    Tk::pack(".info_frame.quit") -side("right") -fill("y");
    Tk::pack(".info_frame.camera") -side("left") -fill(both) -expand(true);
    Tk::pack(".info_frame") -side("top") -fill(both) -expand(true);

    // setup events callbacks
    Tk::bind(".c", "<B1-Motion>", &ClientController::onMouseMotion, event_x, event_y);
    Tk::bind(".c", "<ButtonPress-1>", &ClientController::onMousePress, event_x, event_y);
    Tk::bind(".c", "<ButtonRelease-1>", &ClientController::onMouseRelease, event_x, event_y);
    Tk::bind(".", "<Key-w>", &ClientController::onKeyW);
    Tk::bind(".", "<Key-a>", &ClientController::onKeyA);
    Tk::bind(".", "<Key-s>", &ClientController::onKeyS);
    Tk::bind(".", "<Key-d>", &ClientController::onKeyD);

    m_rendmgr->addAmbientLight(rend::Color3(255, 255, 255));
    m_rendmgr->addDirectionalLight(rend::Color3(255, 255, 255), math::vec3(-1, -1, 0));
}

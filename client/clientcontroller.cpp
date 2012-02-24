#include "clientcontroller.h"

#include <third-party/cpptk-1.0.2/cpptk.h>

using namespace Tk;
using namespace base;
using namespace math;

void ClientController::onMouseMotion(int x, int y)
{
    static int yaw, pitch;
    static int prevX, prevY;
    ClientController *m_this = dynamic_cast<ClientController *>(ptr());

    int dx = prevX - x;
    int dy = prevY - y;
    yaw += dx;
    pitch += dy;
    if (abs(yaw) > 360) yaw %= 360;
    if (abs(pitch) > 360) pitch %= 360;
    m_this->m_mainCam->buildCamMatrix(yaw, pitch, 0);

    prevX = x;
    prevY = y;

    (".info_frame.camera" << Tk::configure()) -text(m_this->m_mainCam->state());
}

void ClientController::onKeyW()
{
    ClientController *m_this = dynamic_cast<ClientController *>(ptr());
    vec3 pos = m_this->m_mainCam->getPosition();
    vec3 dir = m_this->m_mainCam->getDirection();

    pos.z += 5;
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
    pos.z += -5;
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
    : base::Controller(argv, conf)
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
    Tk::bind(".", "<Key-w>", &ClientController::onKeyW);
    Tk::bind(".", "<Key-a>", &ClientController::onKeyA);
    Tk::bind(".", "<Key-s>", &ClientController::onKeyS);
    Tk::bind(".", "<Key-d>", &ClientController::onKeyD);
}

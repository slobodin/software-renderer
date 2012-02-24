#include "clientcontroller.h"

#include <third-party/cpptk-1.0.2/cpptk.h>

using namespace Tk;
using namespace base;
using namespace math;

void ClientController::onMouseMotion(int x, int y)
{
    static int yaw, pitch;
    static int prevX, prevY;

    int dx = prevX - x;
    int dy = prevY - y;
    yaw += dx;
    pitch += dy;
    if (abs(yaw) > 360) yaw %= 360;
    if (abs(pitch) > 360) pitch %= 360;
    m_instance->camera()->buildCamMatrix(yaw, pitch, 0);

    prevX = x;
    prevY = y;

    (".info_frame.camera" << Tk::configure()) -text(m_instance->camera()->state());
//    std::stringstream ss;
//    ss << "yaw: " << yaw;
//    ss << "\npitch: " << pitch;
//    (".info_frame.camera" << Tk::configure()) -text(ss.str());
}

void ClientController::onKeyW()
{
    *syslog << "w" << logmess;
    vec3 pos = m_instance->camera()->getPosition();
    vec3 dir = m_instance->camera()->getDirection();

    pos.z += 5;
    m_instance->camera()->setPosition(pos);

    (".info_frame.camera" << Tk::configure()) -text(m_instance->camera()->state());
}

void ClientController::onKeyA()
{
}

void ClientController::onKeyS()
{
    *syslog << "s" << logmess;
    vec3 pos = m_instance->camera()->getPosition();
    pos.z += -5;
    m_instance->camera()->setPosition(pos);

    (".info_frame.camera" << Tk::configure()) -text(m_instance->camera()->state());
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

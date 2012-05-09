/*
 * clientcontroller.cpp
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#include "clientcontroller.h"

#include <third-party/cpptk-1.0.2/cpptk.h>
#include "light.h"

using namespace Tk;
using namespace base;
using namespace math;

ClientController *ClientController::m_this = 0;

void ClientController::onMouseMotion(int x, int y)
{
    static int yaw, pitch;

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
    m_this->m_prevMouseX = x;
    m_this->m_prevMouseY = y;
}

void ClientController::onMouseRelease(int x, int y)
{
    m_this->m_prevMouseX = x;
    m_this->m_prevMouseY = y;
}

void ClientController::onKeyW()
{
    vec3 pos = m_this->m_mainCam->getPosition();
    vec3 dir = m_this->m_mainCam->getDirection();

    vec3 delta = 5.0 * dir;
    pos += delta;

    m_this->m_mainCam->setPosition(pos);

    (".info_frame.camera" << Tk::configure()) -text(m_this->m_mainCam->state());
}

void ClientController::onKeyA()
{
}

void ClientController::onKeyS()
{
    vec3 pos = m_this->m_mainCam->getPosition();
    vec3 dir = m_this->m_mainCam->getDirection();

    vec3 delta = 5.0 * dir;
    pos -= delta;

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

void ClientController::TkUpdate()
{
    m_this->m_rendmgr->update(m_this->m_rendDevice);

    Tk::afteridle(m_this->m_updateCallback);
}

ClientController::ClientController(char *argv[], const string &conf)
    : base::Controller(argv, conf),
      m_prevMouseX(0),
      m_prevMouseY(0)
{
    m_this = this;

    Tk::init(argv[0]);

    Tk::wm(Tk::title, ".", "Result");

    // create rendering canvas
    Tk::images(Tk::create, Tk::photo, "canvas_photo")
            -Tk::width(m_mainCam->width())
            -Tk::height(m_mainCam->height());

    Tk::frame(".canvas_frame");
    Tk::canvas(".canvas_frame.c") -Tk::highlightthickness(0)
            -Tk::width(m_mainCam->width())
            -Tk::height(m_mainCam->height());

    Tk::pack(".canvas_frame.c") -side("top");
    Tk::pack(".canvas_frame") -side("left");

    (".canvas_frame.c" << Tk::create(Tk::image, 0, 0)) -Tk::image("canvas_photo") -Tk::anchor(nw);

    m_rendDevice = make_shared<rend::RenderDeviceTk>("canvas_photo");
    setDevice(m_rendDevice);

    // setup update event
    m_updateCallback = Tk::callback(&ClientController::TkUpdate);
    Tk::after(500, m_updateCallback);

    // crete gui controls
    Tk::frame(".info_frame");

    Tk::label(".info_frame.camera") -Tk::width(50) -Tk::height(5)
            -anchor(nw) -justify(left);
    Tk::button(".info_frame.quit") -text("Quit") -command(&ClientController::exit);

    Tk::pack(".info_frame.quit") -side("bottom");
    Tk::pack(".info_frame.camera") -side("top");
    Tk::pack(".info_frame") -side("right");

    // setup events callbacks
    Tk::bind(".canvas_frame.c", "<B1-Motion>", &ClientController::onMouseMotion, event_x, event_y);
    Tk::bind(".canvas_frame.c", "<ButtonPress-1>", &ClientController::onMousePress, event_x, event_y);
    Tk::bind(".canvas_frame.c", "<ButtonRelease-1>", &ClientController::onMouseRelease, event_x, event_y);
    Tk::bind(".", "<Key-w>", &ClientController::onKeyW);
    Tk::bind(".", "<Key-a>", &ClientController::onKeyA);
    Tk::bind(".", "<Key-s>", &ClientController::onKeyS);
    Tk::bind(".", "<Key-d>", &ClientController::onKeyD);
}

void ClientController::run()
{
    Tk::runEventLoop();
}

/*
 * unixapplication.cpp
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#include "unixapplication.h"
#include "xviewport.h"
#include <X11/Xutil.h>

UnixApplication::UnixApplication(int argc, const char *argv[])
    : platform::BaseApp()
{
    m_clientController = boost::make_shared<base::Controller>(argc, argv);

    m_playerCamera = m_clientController->getCamera();

    m_clientController->setViewport(boost::make_shared<XViewport>(640, 480, m_playerCamera));
    m_viewport = boost::dynamic_pointer_cast<XViewport>(m_clientController->getViewport());
}

UnixApplication::~UnixApplication()
{
}

void UnixApplication::onFrameStart()
{
}

void UnixApplication::onFrameEnd()
{
}

void UnixApplication::onMouseEvent(const platform::MouseEvent &ev)
{
    if (ev.isLeftPressed())
        std::cerr << "Left pressed\n";
    if (ev.isRightPressed())
        std::cerr << "Right pressed\n";
    if (ev.isMiddlePressed())
        std::cerr << "Middle pressed\n";

    std::cerr << "x: " << ev.x << " y: " << ev.y << "\n";
}

void UnixApplication::onKeyPressed(const platform::KeyboardEvent &ev)
{
//    if (ev.keycode() == platform::KEY_NONE)
//        std::cerr << "Key none!\n";

//    std::cerr << "Getted keycode: " << std::hex << ev.keycode() << "\n";
}

void UnixApplication::onKeyReleased(const platform::KeyboardEvent &ev)
{
//    if (ev.keycode() == platform::KEY_NONE)
//        std::cerr << "Key none!\n";

//    std::cerr << "Getted keycode: " << std::hex << ev.keycode() << "\n";
}

void UnixApplication::onResize(int w, int h)
{
}

int UnixApplication::run()
{
    XEvent report;

    static int a;

    while (1)
    {
        XNextEvent(m_viewport->getXDisplay(), &report);

        switch (report.type)
        {
        case Expose:
            std::cerr << "Exposing\n";
            break;

        case MotionNotify:
        {
            platform::MouseEvent mouseEvent;

            mouseEvent.x = report.xbutton.x;
            mouseEvent.y = report.xbutton.y;

            mouseEvent.buttonsState = (report.xbutton.state & Button1Mask)
                    ? platform::MouseEvent::LEFT_PRESSED : 0;
            mouseEvent.buttonsState |= (report.xbutton.state & Button3Mask)
                    ? platform::MouseEvent::RIGHT_PRESSED : 0;
            mouseEvent.buttonsState |= (report.xbutton.state & Button2Mask)
                    ? platform::MouseEvent::MIDDLE_PRESSED : 0;

            onMouseEvent(mouseEvent);
        }
            break;

        case ButtonRelease:
        case ButtonPress:
        {
            platform::MouseEvent mouseEvent;

            mouseEvent.x = report.xbutton.x;
            mouseEvent.y = report.xbutton.y;
            mouseEvent.buttonsState = (report.xbutton.state & Button1Mask)
                    ? platform::MouseEvent::LEFT_PRESSED : 0;
            mouseEvent.buttonsState |= (report.xbutton.state & Button3Mask)
                    ? platform::MouseEvent::RIGHT_PRESSED : 0;
            mouseEvent.buttonsState |= (report.xbutton.state & Button2Mask)
                    ? platform::MouseEvent::MIDDLE_PRESSED : 0;

            switch(report.xbutton.button)
            {
            case Button1:
                mouseEvent.buttonsState ^= platform::MouseEvent::LEFT_PRESSED;
                break;

            case Button3:
                mouseEvent.buttonsState ^= platform::MouseEvent::RIGHT_PRESSED;
                break;

            case Button2:
                mouseEvent.buttonsState ^= platform::MouseEvent::MIDDLE_PRESSED;
                break;
            }

            onMouseEvent(mouseEvent);
        }
            break;

        case KeyPress:
        {
            static char keyStr[20];
            static KeySym keySym;

            XLookupString(&report.xkey, keyStr, sizeof(keyStr), &keySym, 0);

            platform::KeyboardEvent kbEvent(keySym);

            onKeyPressed(kbEvent);
        }
            break;

        case KeyRelease:
        {
            static char keyStr[20];
            static KeySym keySym;

            XLookupString(&report.xkey, keyStr, sizeof(keyStr), &keySym, 0);

            platform::KeyboardEvent kbEvent(keySym);

            onKeyReleased(kbEvent);
        }
            break;

        default:

//            BaseApp::run();
            break;
        }
    }

    return 0;
}

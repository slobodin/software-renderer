/*
 * application.h
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#ifndef APPLICATION_H
#define APPLICATION_H

#include "renderer.h"

//! IT'S ALL DEPRECATED!

class Application : public platform::BaseAppLinux
{
    sptr(rend::Camera) m_playerCamera;
    sptr(rend::SceneObject) m_hammer;
    sptr(rend::SceneObject) m_sphere;

    void setWindowTitle(const string &title);

protected:
    void update(float dt);

public:
    Application(int argc, const char *argv[]);
    virtual ~Application();

    virtual void onFrameStart();
    virtual void onFrameEnd();

    virtual void onMouseEvent(const platform::MouseEvent &ev);

    virtual void onKeyPressed(const platform::KeyboardEvent &ev);
    virtual void onKeyReleased(const platform::KeyboardEvent &ev);
};

#endif // APPLICATION_H

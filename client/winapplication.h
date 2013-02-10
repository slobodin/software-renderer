/*
 * winapplication.h
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#ifndef WINAPPLICATION_H
#define WINAPPLICATION_H

#include "renderer.h"

class WinApplication : public platform::BaseAppWin
{
    sptr(rend::Camera) m_playerCamera;
    sptr(rend::SceneObject) m_hammer;
    sptr(rend::SceneObject) m_sphere;

protected:
    void update(float dt);

public:
    WinApplication(int argc, const char *argv[]);
    ~WinApplication();

    virtual void onFrameStart();
    virtual void onFrameEnd();

    // this func gets dx, dy, not actual x and y as ev fields
    virtual void onMouseEvent(const platform::MouseEvent &ev);

    // receives only w a s d keys
    virtual void onKeyPressed(const platform::KeyboardEvent &ev);
    virtual void onKeyReleased(const platform::KeyboardEvent &ev);
};

#endif // WINAPPLICATION_H

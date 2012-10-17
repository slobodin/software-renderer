/*
 * example3application.h
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#ifndef EXAMPLE3APPLICATION_H
#define EXAMPLE3APPLICATION_H

#include "renderer.h"

class Example3Application : public platform::BaseAppTk
{
    sptr(rend::Camera) m_playerCamera;
    sptr(rend::SceneObject) m_sphere;

    sptr(rend::TextObject) m_fpsLabel;

protected:
    void update(float dt);

public:
    Example3Application(int argc, const char *argv[]);
    ~Example3Application();

    virtual void onFrameStart();
    virtual void onFrameEnd();

    // this func gets dx, dy, not actual x and y as ev fields
    virtual void onMouseEvent(const platform::MouseEvent &ev);

    // recieves only w a s d keys
    virtual void onKeyPressed(const platform::KeyboardEvent &ev);
    virtual void onKeyReleased(const platform::KeyboardEvent &ev);
};

#endif // EXAMPLE3APPLICATION_H

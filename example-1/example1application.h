/*
 * example1application.h
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#ifndef EXAMPLE1APPLICATION_H
#define EXAMPLE1APPLICATION_H

#include "renderer.h"

class Example1Application : public platform::BaseAppTk
{
    sptr(rend::Camera) m_playerCamera;
    sptr(rend::SceneObject) m_hammer;
    sptr(rend::SceneObject) m_sphere;
    sptr(rend::SceneObject) m_lightPoint;

    sptr(rend::TextObject) m_fpsLabel;

protected:
    void update(float dt);

public:
    Example1Application(int argc, const char *argv[]);
    ~Example1Application() { }

    virtual void onFrameStart() { }
    virtual void onFrameEnd() { }

    // this func gets dx, dy, not actual x and y as ev fields
    virtual void onMouseEvent(const platform::MouseEvent &ev);

    // recieves only w a s d keys
    virtual void onKeyPressed(const platform::KeyboardEvent &ev);
    virtual void onKeyReleased(const platform::KeyboardEvent &/*ev*/) { }
};

#endif // EXAMPLE1APPLICATION_H

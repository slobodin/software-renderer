/*
 * tkapplication.h
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#ifndef TKAPPLICATION_H
#define TKAPPLICATION_H

#include "renderer.h"

class TkApplication : public platform::BaseAppTk
{
    sptr(rend::Camera) m_playerCamera;
    sptr(rend::SceneObject) m_hammer;
    sptr(rend::SceneObject) m_sphere;

protected:
    void update(float dt);

public:
    TkApplication(int argc, const char *argv[]);
    ~TkApplication();

    virtual void onFrameStart();
    virtual void onFrameEnd();

    // this func gets dx, dy, not actual x and y as ev fields
    virtual void onMouseEvent(const platform::MouseEvent &ev);

    // recieves only w a s d keys
    virtual void onKeyPressed(const platform::KeyboardEvent &ev);
    virtual void onKeyReleased(const platform::KeyboardEvent &ev);
};

#endif // TKAPPLICATION_H

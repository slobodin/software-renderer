/*
 * baseapp.h
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#ifndef BASEAPP_H
#define BASEAPP_H

namespace base
{
class Controller;
}

namespace platform
{

struct MouseEvent;
struct KeyboardEvent;

class BaseApp
{
protected:
    static BaseApp *m_this;

    sptr(base::Controller) m_clientController;

    static void exit() { ::exit(0); }

    //! This func calls every frame.
    /** Receives dt in msecs*/
    virtual void update(float dt) = 0;

public:
    static BaseApp *instance() { return m_this; }

    BaseApp();
    virtual ~BaseApp();

    virtual void onFrameStart() = 0;
    virtual void onFrameEnd() = 0;

    virtual void onMouseEvent(const MouseEvent &ev) = 0;

    virtual void onKeyPressed(const KeyboardEvent &ev) = 0;
    virtual void onKeyReleased(const KeyboardEvent &ev) = 0;

    virtual void onResize(int w, int h) = 0;

    // TODO: rename to run frame
    virtual int run();

    NONCOPYABLE(BaseApp)
};

}

#endif // BASEAPP_H

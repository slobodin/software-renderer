/*
 * baseapptk.h
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#ifndef BASEAPPTK_H
#define BASEAPPTK_H

#ifdef TK_VERSION

#include "comm_pch.h"

#include "baseapp.h"
#include "viewport.h"
#include "events.h"

namespace platform
{

class TkViewport;

class BaseAppTk : public BaseApp
{
    static void tkUpdate();

    MouseEvent mouseEvPrev;

    static void tkMouseMotion(int x, int y);
    static void tkMousePress(int x, int y);
    static void tkMouseRelease(int x, int y);

    static void tkKeyW();
    static void tkKeyA();
    static void tkKeyS();
    static void tkKeyD();

    static BaseAppTk *m_instance;
    string m_updateCallback;

protected:
    sptr(TkViewport) m_viewport;

public:
    BaseAppTk(int argc, const char *argv[]);
    ~BaseAppTk();

    virtual void onResize(int w, int h);

    virtual int run();
};

class TkViewport : public rend::Viewport
{
    std::string m_frameName;

    virtual void resize(int w, int h);

public:
    TkViewport(int width, int height, boost::shared_ptr<rend::Camera> camera);
    virtual ~TkViewport();

    void setFrameName(const std::string &name);

    void flush(const unsigned char * const pixels);
};

}

#endif

#endif // BASEAPPTK_H

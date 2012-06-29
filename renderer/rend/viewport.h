/*
 * renderdevice.h
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#ifndef VIEWPORT_H
#define VIEWPORT_H

#include "comm_pch.h"

namespace rend
{

class FrameBuffer;
class Camera;
class RenderMgr;

class Viewport : boost::noncopyable
{
protected:
    //! Screen width.
    int m_width;
    //! Screen height.
    int m_height;
    //! Screen X center point.
    int m_centerX;
    //! Screen Y center point.
    int m_centerY;
    //! Aspect ratio. Width / height.
    double m_aspect;

    boost::shared_ptr<Camera> m_camera;

    friend class RenderMgr;
    void resize(int w, int h);

public:
    Viewport(int width, int height, boost::shared_ptr<Camera> camera);
    virtual ~Viewport();

    int                 getWidth() const;
    int                 getHeight() const;
    int                 getAspect() const;
    std::pair<int, int> getCenter() const;

    virtual void frameBegin() = 0;
    virtual void flush(unsigned char *pixels) = 0;
};

}

#endif // VIEWPORT_H

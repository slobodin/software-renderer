/*
 * viewport.h
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#ifndef VIEWPORT_H
#define VIEWPORT_H

namespace rend
{

const int DEFAULT_WIDTH = 640;
const int DEFAULT_HEIGHT = 480;

class Camera;
class RenderMgr;

class Viewport
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
    float m_aspect;

    sptr(Camera) m_camera;

    friend class RenderMgr;
    virtual void resize(int w, int h);

public:
    Viewport(int width, int height, sptr(Camera) camera);
    virtual ~Viewport();

    int                 getWidth() const;
    int                 getHeight() const;
    float               getAspect() const;
    std::pair<int, int> getCenter() const;

    sptr(Camera) getCamera() const { return m_camera; }

    virtual void flush(const unsigned char *const pixels) = 0;

    NONCOPYABLE(Viewport)
};

}

#endif // VIEWPORT_H

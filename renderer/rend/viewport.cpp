/*
 * renderdevice.cpp
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#include "viewport.h"
#include "camera.h"

namespace rend
{

Viewport::Viewport(int width, int height, boost::shared_ptr<Camera> camera)
    : m_width(width),
      m_height(height),
      m_camera(camera)
{
    if (m_width <= 0)
    {
        syslog << "Invalid width. Setting default." << logwarn;
        m_width = DEFAULT_WIDTH;
    }
    if (m_height <= 0)
    {
        syslog << "Invalid height. Setting default." << logwarn;
        m_height = DEFAULT_HEIGHT;
    }

    syslog << "Viewport size [" << m_width << "," << m_height << "]" << logmess;

    resize(m_width, m_height);
}

Viewport::~Viewport()
{
}

int Viewport::getWidth() const
{
    return m_width;
}

int Viewport::getHeight() const
{
    return m_height;
}

int Viewport::getAspect() const
{
    return m_aspect;
}

std::pair<int, int> Viewport::getCenter() const
{
    return std::pair<int, int>(m_centerX, m_centerY);
}

void Viewport::resize(int w, int h)
{
    if (!m_camera)
    {
        syslog << "Can't resize viewport. No active camera." << logerr;
        return;
    }

    if (w <= 0 || h <= 0)
    {
        syslog << "Can't resize viewport. Invalid width and height values." << logerr;
        return;
    }

    m_width = w;
    m_height = h;

    m_centerX = (m_width - 1) / 2;
    m_centerY = (m_height - 1) / 2;
    m_aspect = m_width / m_height;

    // update cam
    m_camera->m_viewPlaneWidth = 2.0;
    m_camera->m_viewPlaneHeight = 2.0 / m_aspect;

    m_camera->m_distance = 0.5 * m_camera->m_viewPlaneWidth * (1.0 / tan(math::DegToRad(m_camera->m_fov / 2.0)));
}

}

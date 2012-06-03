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
    m_centerX = (m_width - 1) / 2;
    m_centerY = (m_height - 1) / 2;
    m_aspect = m_width / m_height;

    resize(m_width, m_height);
}

void Viewport::resize(int w, int h)
{
    if (!m_camera)
    {
        *syslog << "Can't resize viewport. No active camera." << logerr;
        return;
    }

    if (w <= 0 || h <= 0)
    {
        *syslog << "Can't resize viewport. Invalid width and height values." << logerr;
        return;
    }

    // update cam
    m_camera->m_viewPlaneWidth = 2.0;
    m_camera->m_viewPlaneHeight = 2.0 / m_aspect;

    m_camera->m_distance = 0.5 * m_camera->m_viewPlaneWidth * tan(math::DegToRad(m_camera->m_fov / 2));
}

}

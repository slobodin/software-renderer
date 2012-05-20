/*
 * camera.h
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#ifndef CAMERA_H
#define CAMERA_H

#include "comm_pch.h"

#include "vec3.h"
#include "m44.h"
#include "renderlist.h"

namespace rend
{

//! Scene camera.
/*!
  *
  */
class Camera
{
    //! Camera viewport.
    /*! 2D rectangle that represents screen. */
    struct ViewPort
    {
        double width;
        double height;
        double centerX;
        double centerY;
    };

    //! Position of the camera in the world.
    math::vec3 m_position;
    //! Right vector.
    math::vec3 m_right;
    //! Up vector.
    math::vec3 m_up;
    //! Direction vector.
    math::vec3 m_dir;

    //! Field of view. Default is 90 grad.
    double m_fov;
    //! Aspect ratio. Width / height.
    double m_aspect;

    //! Near Z-clipping plane position.
    double m_nearZ;
    //! Far Z-clipping plane position.
    double m_farZ;

    ViewPort m_viewPort;

    //! Normalized projected plane size.
    double m_viewPlaneWidth;
    double m_viewPlaneHeight;
    //! Distance from the (0, 0, 0) to the projected plane along Z axis.
    double m_distance;

    math::M44 m_worldToCamera;
    math::M44 m_projection;
    math::M44 m_screen;

public:
    //! Default ctor.
    /*! Initialize camera with position, screen width and height,
      * field of view (default 90 gr.), near and far clipping planes */
    Camera(const math::vec3 position,
           double width,
           double height,
           double fov = 90.0,
           double nearZ = 5.0,
           double farZ = 15000.0);
    ~Camera() { }

    //! Screen width.
    int width() const { return m_viewPort.width; }
    //! Screen height.
    int height() const { return m_viewPort.height; }
    //! Resize our screen.
    void resize(int w, int h);

    void setPosition(const math::vec3 &pos);
    math::vec3 getPosition() const { return m_position; }
    void setDirection(const math::vec3 &dir);
    math::vec3 getDirection() const { return m_dir; }

    //! Build matrix with 3 Euler angles (degrees).
    void buildCamMatrix(const double yaw, const double pitch, const double roll);
    //! Build matrix using right, up and direction vector.
    void buildCamMatrix(const math::vec3 &lookAtPoint);
    //! 
    void buildCamMatrix(const math::vec3 &lookFrom, const math::vec3 &lookTo);

    template<typename T>
    void apply(T &container) const;
    void apply(math::vec3 &v) const;

    void toCamera(RenderList &rendList) const;
    void toScreen(math::vec3 &v) const;
    void toScreen(RenderList &rendList) const;

    bool culled(const Mesh &obj) const;

    string state() const;
};

template<typename T>
void Camera::apply(T &container) const
{
    foreach (T &v, container)
    {
        apply(v);
    }
}

inline void Camera::apply(math::vec3 &v) const
{
    // world to cam transformation
    v = v * m_worldToCamera;

    toScreen(v);
}

}

#endif // CAMERA_H

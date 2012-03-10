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
#include "affinetransform.h"
#include "renderlist.h"

namespace rend
{

class Camera
{
    struct ViewPort
    {
        double width;
        double height;
        double centerX;
        double centerY;
    };

private:
    math::vec3 m_position;
    math::vec3 m_right;
    math::vec3 m_up;
    math::vec3 m_dir;

    double m_fov;
    double m_aspect;

    double m_nearZ;
    double m_farZ;

    ViewPort m_viewPort;

    double m_viewPlaneWidth;
    double m_viewPlaneHeight;

    double m_distance;

    math::AffineTransform m_worldToCamera;
    math::AffineTransform m_projection;
    math::AffineTransform m_screen;

public:
    Camera(const math::vec3 position,
           const double width,
           const double height,
           const double fov = 90.0,
           const double nearZ = 5.0,
           const double farZ = 15000.0);
    ~Camera();

    int width() const;
    int height() const;
    void resize(int w, int h);

    string state() const;

    void setPosition(const math::vec3 &pos);
    math::vec3 getPosition() const;
    math::vec3 getDirection() const;

    //! build matrix with 3 Euler angles (degrees)
    void buildCamMatrix(const double yaw, const double pitch, const double roll);
    //! build matrix using right, up and direction vector
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
    m_worldToCamera.transformPoint(v);

    toScreen(v);
}

}

#endif // CAMERA_H

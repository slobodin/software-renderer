#ifndef CAMERA_H
#define CAMERA_H

#include "comm_pch.h"

#include "vec3.h"
#include "affinetransform.h"

namespace rend
{

class Frustum
{

};

struct ViewPort
{
    double width;
    double height;
    double centerX;
    double centerY;
};

class Camera
{
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
           const double farZ = 500.0);
    ~Camera();

    void setPosition(const math::vec3 &pos);
    math::vec3 getPosition() const;
    //! build matrix with 3 Euler angles
    void buildCamMatrix(const double yaw, const double pitch, const double roll);
    //! build matrix using right, up and direction vector
    void buildCamMatrix(const math::vec3 &lookAtPoint);
    //! 
    void buildCamMatrix(const math::vec3 &lookFrom, const math::vec3 &lookTo);

    void apply(list<math::vec3> &vlist) const;
    void apply(vector<math::vec3> &vlist) const;
};

}

#endif // CAMERA_H

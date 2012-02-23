#include "camera.h"

namespace rend
{

Camera::Camera(const math::vec3 position,
               const double width,
               const double height,
               const double fov,
               const double nearZ,
               const double farZ)
    : m_position(position),
      m_right(1.0, 0.0, 0.0),
      m_up(0.0, 1.0, 0.0),
      m_dir(0.0, 0.0, 1.0),
      m_fov(fov),
      m_nearZ(nearZ),
      m_farZ(farZ)
{
    m_viewPort.width = width;
    m_viewPort.height = height;
    m_viewPort.centerX = (m_viewPort.width - 1) / 2;
    m_viewPort.centerY = (m_viewPort.height - 1) / 2;

    m_aspect = m_viewPort.width / m_viewPort.height;

    m_viewPlaneWidth = 2.0;
    m_viewPlaneHeight = 2.0 / m_aspect;

    m_distance = 0.5 * m_viewPlaneWidth * tan(math::DegToRad(m_fov / 2));
}

Camera::~Camera()
{
}

void Camera::setPosition(const math::vec3 &pos)
{
    m_position = pos;
    m_worldToCamera.setv(-m_position);
}

math::vec3 Camera::getPosition() const
{
    return m_position;
}

void Camera::buildCamMatrix(const double yaw, const double pitch, const double roll)
{
/*    // find rotation matrix 
    math::M33 rot = math::M33::getRotateYawPitchRollMatrix(-yaw, -pitch, -roll);

    // note: we don't recalculate right, up and dir vectors
    m_worldToCamera.setm(rot);
    m_worldToCamera.setv(-m_position); */

    m_dir = math::vec3(0.0, 0.0, 1.0);
    m_right = math::vec3(1.0, 0.0, 0.0);
    m_up = math::vec3(0.0, 1.0, 0.0);

    math::M33 rot = math::M33::getRotateYawPitchRollMatrix(-yaw, -pitch, -roll);
    m_dir = rot * m_dir;
    m_right = rot * m_right;
    m_up = rot * m_up;

    m_dir.normalize();
    double dot = m_up.dotProduct(m_dir);
    math::vec3 temp = dot * m_dir;
    m_up -= temp;

    m_right = m_up.crossProduct(m_dir);

    m_up.normalize();
    m_right.normalize();

    m_worldToCamera.setm(rot);
    m_worldToCamera.setv(-m_position);
}

void Camera::buildCamMatrix(const math::vec3 &lookAtPoint)
{
    // direction = target - camera_poition
    m_dir = lookAtPoint - m_position;

    // up is Y
    m_up.set(0.0, 1.0, 0.0);
    // find right vector
    m_right = m_up.crossProduct(m_dir);
    // find up vector
    m_up = m_dir.crossProduct(m_right);

    m_right.normalize();
    m_up.normalize();
    m_dir.normalize();

    // create matrix
    math::M33 resM(m_right.x, m_up.x, m_dir.x,
                    m_right.y, m_up.y, m_dir.y,
                    m_right.z, m_up.z, m_dir.z);

    m_worldToCamera.setm(resM);
    m_worldToCamera.setv(-m_position);
}

void Camera::buildCamMatrix(const math::vec3 &lookFrom, const math::vec3 &lookTo)
{
    m_position = lookFrom;
    buildCamMatrix(lookTo);
}

void Camera::apply(list<math::vec3> &vlist) const
{
    list<math::vec3>::iterator v = vlist.begin();

    while (v != vlist.end())
    {
        // world to cam
        m_worldToCamera.transformPoint(*v);

        // perspective transformation
        double z = v->z;

        assert(z != 0.0);

        v->x = m_distance * v->x / z;
        v->y = m_distance * v->y * m_aspect / z;

        // screen transformation
        double alpha = 0.5 * m_viewPort.width - 0.5;
        double beta = 0.5 * m_viewPort.height - 0.5;

        v->x = alpha + alpha * v->x;
        v->y = beta - beta * v->y;

        v++;
    }
}

void Camera::apply(vector<math::vec3> &vlist) const
{
    vector<math::vec3>::iterator v = vlist.begin();

    while (v != vlist.end())
    {
        // world to cam
        m_worldToCamera.transformPoint(*v);

        // perspective transformation
        double z = v->z;

        assert(z != 0.0);

        v->x = m_distance * v->x / z;
        v->y = m_distance * v->y * m_aspect / z;

        // screen transformation
        double alpha = 0.5 * m_viewPort.width - 0.5;
        double beta = 0.5 * m_viewPort.height - 0.5;

        v->x = alpha + alpha * v->x;
        v->y = beta - beta * v->y;

        v++;
    }
}

}

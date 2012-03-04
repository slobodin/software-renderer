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
    resize(width, height);
}

Camera::~Camera()
{
}

int Camera::width() const
{
    return m_viewPort.width;
}

int Camera::height() const
{
    return m_viewPort.height;
}

void Camera::resize(int w, int h)
{
    m_viewPort.width = w;
    m_viewPort.height = h;
    m_viewPort.centerX = (m_viewPort.width - 1) / 2;
    m_viewPort.centerY = (m_viewPort.height - 1) / 2;

    m_aspect = m_viewPort.width / m_viewPort.height;

    m_viewPlaneWidth = 2.0;
    m_viewPlaneHeight = 2.0 / m_aspect;

    m_distance = 0.5 * m_viewPlaneWidth * tan(math::DegToRad(m_fov / 2));
}

string Camera::state() const
{
    std::ostringstream out;
    out << "Camera:\n";
    out << "    -position: " << m_position << "\n";
    out << "    -dir: " << m_dir << "\n";
    out << "    -up: " << m_up << "\n";
    out << "    -right: " << m_right << "\n";

    return out.str();
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

math::vec3 Camera::getDirection() const
{
    return m_dir;
}

void Camera::buildCamMatrix(const double yaw, const double pitch, const double roll)
{
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

void Camera::toCamera(RenderList &rendList) const
{
    list<math::Triangle> &trias = rendList.triangles();
    list<math::Triangle>::iterator t = trias.begin();

    while (t != trias.end())
    {
        math::vec3 &p1 = t->v(0);
        math::vec3 &p2 = t->v(1);
        math::vec3 &p3 = t->v(2);

        m_worldToCamera.transformPoint(p1);
        m_worldToCamera.transformPoint(p2);
        m_worldToCamera.transformPoint(p3);

        // FIXME:
        if (p1.z < m_distance || p2.z < m_distance || p3.z < m_distance)
        {
            t = trias.erase(t);
            continue;
        }

        t++;
    }
}

void Camera::toScreen(math::vec3 &v) const
{
    // perspective transformation
    double z = v.z;

    assert(z != 0.0);

    v.x = m_distance * v.x / z;
    v.y = m_distance * v.y * m_aspect / z;

    // screen transformation
    double alpha = 0.5 * m_viewPort.width - 0.5;
    double beta = 0.5 * m_viewPort.height - 0.5;

    v.x = alpha + alpha * v.x;
    v.y = beta - beta * v.y;
}

void Camera::toScreen(RenderList &rendList) const
{
    list<math::Triangle> &trias = rendList.triangles();
    list<math::Triangle>::iterator t = trias.begin();

    while (t != trias.end())
    {
        math::vec3 &p1 = t->v(0);
        math::vec3 &p2 = t->v(1);
        math::vec3 &p3 = t->v(2);

        toScreen(p1);
        toScreen(p2);
        toScreen(p3);

        t++;
    }
}

bool Camera::culled(const Mesh &obj) const
{
    math::vec3 spherePos = obj.position();
    double radius = obj.bsphere().radius();
    m_worldToCamera.transformPoint(spherePos);

    // check Z plane
    if (((spherePos.z - radius) > m_farZ) ||
            ((spherePos.z + radius) < m_nearZ))
        return true;

    return false;
}

}

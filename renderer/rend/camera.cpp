/*
 * camera.cpp
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#include "camera.h"

#include "m33.h"
#include "renderlist.h"
#include "viewport.h"
#include "sceneobject.h"
#include "mesh.h"

namespace rend
{

Camera::Camera(const math::vec3 position,
               double fov,
               double nearZ,
               double farZ)
    : m_position(position),
      m_right(1.0, 0.0, 0.0),
      m_up(0.0, 1.0, 0.0),
      m_dir(0.0, 0.0, 1.0),
      m_yaw(0),
      m_pitch(0),
      m_roll(0),
      m_fov(fov),
      m_nearZ(nearZ),
      m_farZ(farZ)
{
}

void Camera::setPosition(const math::vec3 &pos)
{
    m_position = pos;

    // position changed -> translation matrix changed
    buildCamMatrix();
}

math::vec3 Camera::getPosition() const
{
    return m_position;
}

void Camera::setDirection(const math::vec3 &dir)
{
    m_dir = dir;
    m_dir.normalize();

    // direction changed -> up and right vectors changed -> rotation matrix changed
    buildCamMatrix();
}

math::vec3 Camera::getDirection() const
{
    return m_dir;
}

math::vec3 Camera::getRightVector() const
{
    return m_right;
}

math::vec3 Camera::getUpVector() const
{
    return m_up;
}

void Camera::setEulerAnglesRotation(double yaw, double pitch, double roll)
{
    m_yaw = yaw;
    m_pitch = pitch;
    m_roll = roll;

    buildCamMatrix();
}

void Camera::buildCamMatrix()
{
    // get rotation matrices
    math::M33 mxinv = math::M33::getRotateXMatrix(m_pitch).invert();
    math::M33 myinv = math::M33::getRotateYMatrix(m_yaw).invert();
    math::M33 mzinv = math::M33::getRotateZMatrix(m_roll).invert();

    // perform invert rotation
    math::M33 mrot = myinv * mxinv * mzinv;     // in y x z order

    // store cam basis
    m_dir = math::vec3(mrot.x[0][2], mrot.x[1][2], mrot.x[2][2]);
    m_right = math::vec3(mrot.x[0][0], mrot.x[1][0], mrot.x[2][0]);
    m_up = math::vec3(mrot.x[0][1], mrot.x[1][1], mrot.x[2][1]);

    // compute result matrix
    m_worldToCamera.set(-m_position);
    m_worldToCamera *= mrot;

    /*
    // we must set up and right vectors (in order to create camera basis)
    // assume, that we already have proper direction

    // up is Y
    m_up.set(0.0, 1.0, 0.0);
    // find right vector
    m_right = m_up.crossProduct(m_dir);
    // find up vector
    m_up = m_dir.crossProduct(m_right);

    // normalize all vectors
    m_right.normalize();
    m_up.normalize();
    m_dir.normalize();

    // create rotation matrix (like Rx-1 * Ry-1 * Rz-1 matrix in camera implementation with Euler angles)
    math::M33 rotM(m_right.x, m_up.x, m_dir.x,
                   m_right.y, m_up.y, m_dir.y,
                   m_right.z, m_up.z, m_dir.z);

    // create inv translation matrix
    m_worldToCamera.set(-m_position);

    // do not forget to multiply inv translation matrix by rotation matrix
    m_worldToCamera *= rotM;*/
}
/*
void Camera::lookTo(const math::vec3 &lookAtPoint)
{
    // direction = target - camera_poition
    m_dir = lookAtPoint - m_position;
    m_dir.normalize();

    buildCamMatrix();
}

void Camera::lookFromTo(const math::vec3 &lookFrom, const math::vec3 &lookTo)
{
    m_position = lookFrom;
    this->lookTo(lookTo);
}
*/
void Camera::toCamera(RenderList &rendList) const
{
    list<math::Triangle> &trias = rendList.triangles();
    list<math::Triangle>::iterator t = trias.begin();

    while (t != trias.end())
    {
        math::vec3 &p1 = t->v(0).p;
        math::vec3 &p2 = t->v(1).p;
        math::vec3 &p3 = t->v(2).p;

        p1 = p1 * m_worldToCamera;
        p2 = p2 * m_worldToCamera;
        p3 = p3 * m_worldToCamera;

        // FIXME:
        if (p1.z < m_distance || p2.z < m_distance || p3.z < m_distance)
        {
            t = trias.erase(t);
            continue;
        }

        t++;
    }
}

void Camera::toScreen(RenderList &rendList, const Viewport &viewport) const
{
    list<math::Triangle> &trias = rendList.triangles();

    for (auto &t : trias)
    {
        math::vec3 &p1 = t.v(0).p;
        math::vec3 &p2 = t.v(1).p;
        math::vec3 &p3 = t.v(2).p;

        toScreen(p1, viewport);
        toScreen(p2, viewport);
        toScreen(p3, viewport);
    }
}

bool Camera::culled(const SceneObject &obj) const
{
    /*math::vec3 spherePos = obj.getPosition();
    double radius = obj.bsphere().radius();

    // APPLY TRANSFORMATION!

    if (radius < 0)
        return false;

    spherePos = spherePos * m_worldToCamera;

    // check Z plane
    if (((spherePos.z - radius) > m_farZ)
            || ((spherePos.z + radius) < m_nearZ))
        return true;*/

    return false;
}

void Camera::toScreen(math::vec3 &v, const Viewport &viewport) const
{
    // perspective transformation
    double z = v.z;

    assert(z != 0.0);

    v.x = m_distance * v.x / z;
    v.y = m_distance * v.y * viewport.getAspect() / z;

    // screen transformation
    double alpha = 0.5 * viewport.getWidth() - 0.5;
    double beta = 0.5 * viewport.getHeight() - 0.5;

    v.x = alpha + alpha * v.x;
    v.y = beta - beta * v.y;
}

}

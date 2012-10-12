/*
 * model.h
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#ifndef NODE_H
#define NODE_H

#include "comm_pch.h"

#include "vec3.h"
#include "m44.h"
#include "m33.h"

//! Abstract scene object.
/*!
  * Contains information about world transformation and
  * appropriate setters\getters.
  */
class Node
{
protected:
    //! Local to world transformation.
    /*! Applied every frame. */
    math::M44 m_worldTransformation;

public:
    //! Default ctor.
    Node() { }
    //! Dtor.
    virtual ~Node() { }

    //! Sets position in world space.
    virtual void setPosition(const math::vec3 &pos);

    //! Sets rotation in world space by (x, y, z)-angles.
    virtual void setRotation(const math::vec3 &angles);

    //! Sets rotation in world space by yaw pitch roll angles.
    virtual void setRotation(double yaw, double pitch, double roll);

    //! Scales the model.
    virtual void setScale(const math::vec3 &coeff);

    //! Sets the whole affine transformation.
    virtual void setTransformation(const math::M44 &tr);

    virtual void resetTransformation();

    //! Returns model position.
    math::vec3 getPosition() const;

    //! Returns whole world space transformation.
    math::M44 getTransformation() const;
};

inline void Node::setPosition(const math::vec3 &pos)
{
    m_worldTransformation.x[3][0] = pos.x;
    m_worldTransformation.x[3][1] = pos.y;
    m_worldTransformation.x[3][2] = pos.z;
}

inline void Node::setRotation(const math::vec3 &angles)
{
    math::M33 rotM = math::M33::getRotateYawPitchRollMatrix(angles.y,
                                                            angles.x,
                                                            angles.z);

    rotM *= m_worldTransformation.getM();

    m_worldTransformation = math::M44(rotM, m_worldTransformation.getV());
}

inline void Node::setRotation(double yaw, double pitch, double roll)
{
    setRotation(math::vec3(pitch, yaw, roll));
}

inline void Node::setScale(const math::vec3 &coeff)
{
    m_worldTransformation = math::M44(m_worldTransformation.getM() * math::M33::getScaleMatrix(coeff) /* setting scale matrix */,
                                      m_worldTransformation.getV() /* prev translation */);
}

inline void Node::setTransformation(const math::M44 &tr)
{
    m_worldTransformation = tr;
}

inline void Node::resetTransformation()
{
    m_worldTransformation.reset();
}

inline math::vec3 Node::getPosition() const
{
    return math::vec3(m_worldTransformation.x[3][0],
                      m_worldTransformation.x[3][1],
                      m_worldTransformation.x[3][2]);
}

inline math::M44 Node::getTransformation() const
{
    return m_worldTransformation;
}

#endif // NODE_H

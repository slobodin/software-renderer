/*
 * model.h
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#ifndef MODEL_H
#define MODEL_H

#include "comm_pch.h"

#include "vec3.h"
#include "m44.h"
#include "m33.h"

//! Abstract scene object.
/*! Contains information about world transformation and
  * appropriate setters\getters.
  */
class Model
{
protected:
    //! Local to world transformation.
    /*! Applied every frame calling. */
    math::M44 m_worldTransformation;

public:
    Model() { }
    virtual ~Model() { }

    //! Sets position in world space.
    void setPosition(const math::vec3 &pos);

    //! Sets rotation in world space by (x, y, z)-angles.
    void setRotation(const math::vec3 &angles);

    //! Sets rotation in world space by yaw pitch roll angles.
    void setRotation(double yaw, double pitch, double roll);

    //! Scales the model.
    void setScale(const math::vec3 &coeff);

    //! Sets the whole affine transformation.
    void setTransformation(const math::M44 &tr);

    //! Returns model position.
    math::vec3 getPosition() const;

    //! Returns whole world space transformation.
    math::M44 getTransformation() const;
};

inline void Model::setPosition(const math::vec3 &pos)
{
    m_worldTransformation.x[3][0] = pos.x;
    m_worldTransformation.x[3][1] = pos.y;
    m_worldTransformation.x[3][2] = pos.z;
}

inline void Model::setRotation(const math::vec3 &angles)
{
    math::M33 rotM = math::M33::getRotateYawPitchRollMatrix(angles.y,
                                                            angles.x,
                                                            angles.z);
    math::M44 affTr(rotM, /* setting rotation */
                    math::vec3() /* no translation */);

    m_worldTransformation *= affTr;
}

inline void Model::setRotation(double yaw, double pitch, double roll)
{
    setRotation(math::vec3(pitch, yaw, roll));
}

inline void Model::setScale(const math::vec3 &coeff)
{
    m_worldTransformation = math::M44(math::M33::getScaleMatrix(coeff) /* setting scale matrix */,
                                      math::vec3() /* no translation */);
}

inline void Model::setTransformation(const math::M44 &tr)
{
    m_worldTransformation = tr;
}

inline math::vec3 Model::getPosition() const
{
    return math::vec3(m_worldTransformation.x[3][0],
                      m_worldTransformation.x[3][1],
                      m_worldTransformation.x[3][2]);
}

inline math::M44 Model::getTransformation() const
{
    return m_worldTransformation;
}

#endif // MODEL_H

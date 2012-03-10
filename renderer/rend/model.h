/*
 * model.h
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#ifndef MODEL_H
#define MODEL_H

#include "comm_pch.h"

#include "affinetransform.h"
#include "vec3.h"

class Model
{
protected:
    math::AffineTransform m_worldTransformation;

public:
    Model() { }
    virtual ~Model() { }

    void setPosition(const math::vec3 &pos);
    void setRotation(const math::vec3 &angles);
    void setScale(const math::vec3 &coeff);
    void setTransformation(const math::AffineTransform &tr);

    const math::vec3& position() const { return m_worldTransformation.getv(); }
    const math::AffineTransform& transformation() const { return m_worldTransformation; }
};

inline void Model::setPosition(const math::vec3 &pos)
{
    m_worldTransformation.setv(pos);
}

inline void Model::setRotation(const math::vec3 &angles)
{
    math::M33 resM = math::M33::getRotateYawPitchRollMatrix(angles.y,
                                                            angles.x,
                                                            angles.z);
    m_worldTransformation.setm(resM);
}

inline void Model::setScale(const math::vec3 &coeff)
{
    math::M33 resM = math::M33::getScaleMatrix(coeff);
    m_worldTransformation.setm(resM);
}

inline void Model::setTransformation(const math::AffineTransform &tr)
{
    m_worldTransformation = tr;
}

#endif // MODEL_H

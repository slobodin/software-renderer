/*
 * material.h
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#ifndef MATERIAL_H
#define MATERIAL_H

#include "comm_pch.h"

#include "color.h"
#include "resource.h"

namespace rend
{

class Texture;

//! Surface properties.
/*!
  * Holds data about shading mode, diffuse,
  * ambient, specular and emissive reflection coefficients,
  * texture and the list goes on.
  */
struct Material : public base::Resource
{
    enum ShadeMode
    {
        SM_UNDEFINED,
        SM_WIRE,
        SM_PLAIN_COLOR,
        SM_FLAT,
        SM_GOURAUD,
        SM_PHONG,
        SW_TEXTURE
    };

    //! Triangle side type.
    enum SideType
    {
        ONE_SIDE,
        TWO_SIDE
    };

    ShadeMode shadeMode;
    SideType sideType;

    Color3 plainColor;
    Color3 ambientColor;
    Color3 diffuseColor;
    Color3 specularColor;
    Color3 emissiveColor;

    sptr(Texture) m_texture;

    //! Default ctor.
    Material();
};

}

#endif // MATERIAL_H

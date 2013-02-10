/*
 * material.cpp
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#include "stdafx.h"

#include "material.h"

#include "texture.h"

namespace rend
{

Material::Material()
    : shadeMode(SM_WIRE),
      sideType(ONE_SIDE),
      specularColor(0, 0, 0),
      emissiveColor(0, 0, 0),
      alpha(255)
{
}

sptr(Material) Material::clone() const
{
    sptr(Material) newMat = std::make_shared<Material>();

    newMat->shadeMode = shadeMode;
    newMat->sideType = sideType;
    newMat->plainColor = plainColor;
    newMat->ambientColor = ambientColor;
    newMat->diffuseColor = diffuseColor;
    newMat->specularColor = specularColor;
    newMat->emissiveColor = emissiveColor;
    newMat->textureName = textureName;
    if (texture)
        newMat->texture = texture->clone();
    newMat->alpha = alpha;

    return newMat;
}

}

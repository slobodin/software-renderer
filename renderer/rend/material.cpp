/*
 * material.cpp
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#include "material.h"

#include "texture.h"

namespace rend
{

Material::Material()
    : shadeMode(SM_WIRE),
      specularColor(0, 0, 0),
      emissiveColor(0, 0, 0),
      useLighting(true)
{
}

}

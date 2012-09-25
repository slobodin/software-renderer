/*
 * terrainsceneobject.h
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#ifndef TERRAINSCENEOBJECT_H
#define TERRAINSCENEOBJECT_H

#include "comm_pch.h"

#include "sceneobject.h"

namespace rend
{

class Texture;

class TerrainSceneObject : public SceneObject
{
public:
    TerrainSceneObject(double width, double height, double vertScale,
                       const shared_ptr<Texture> heightMap,
                       const shared_ptr<Texture> texture = shared_ptr<Texture>());
};

}

#endif // TERRAINSCENEOBJECT_H

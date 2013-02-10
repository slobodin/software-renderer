/*
 * terrainsceneobject.h
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#ifndef TERRAINSCENEOBJECT_H
#define TERRAINSCENEOBJECT_H

#include "sceneobject.h"

namespace rend
{

class Texture;

class TerrainSceneObject : public SceneObject
{
public:
    TerrainSceneObject(float width, float height, float vertScale,
                       const sptr(Texture) heightMap,
                       const sptr(Texture) texture = std::shared_ptr<Texture>());
};

}

#endif // TERRAINSCENEOBJECT_H

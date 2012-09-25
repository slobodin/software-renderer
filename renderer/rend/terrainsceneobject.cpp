/*
 * terrainsceneobject.cpp
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#include "terrainsceneobject.h"
#include "texture.h"
#include "mesh.h"
#include "vertexbuffer.h"

namespace rend
{

TerrainSceneObject::TerrainSceneObject(double width, double height, double vertScale,
                                       const shared_ptr<Texture> heightMap)
{
    // set name
    setName(string("terrain_") + heightMap->getName());

    if (!heightMap)
        return;

    int columns = heightMap->width();
    int rows = heightMap->height();

    double colStep = width / (double)(columns - 1);
    double rowStep = height / (double)(rows - 1);

    // store all vertices
    vector<math::vertex> vertices;
    for (int currRow = 0; currRow < rows; currRow++)
    {
        for (int currCol = 0; currCol < columns; currCol++)
        {
            math::vertex v;

            v.p.x = currCol * colStep - (width / 2.0);      // (0;0) point is the center of the map
            v.p.z = currRow * rowStep - (height / 2.0);

            // XYNTA:
            v.p.y = (double)heightMap->at(currCol, currRow)[RED] / 255.0;
            v.p.y *= vertScale;

            vertices.push_back(v);
        }
    }

    // create triangles
    vector<int> indices;
    for (int poly = 0; poly < ((columns - 1) * (rows - 1)); poly++)
    {
        int basePolyInd = (poly % (columns - 1)) + (columns * (poly / (columns - 1)));

        indices.push_back(basePolyInd);
        indices.push_back(basePolyInd + columns);
        indices.push_back(basePolyInd + columns + 1);

        indices.push_back(basePolyInd);
        indices.push_back(basePolyInd + columns + 1);
        indices.push_back(basePolyInd + 1);
    }

    VertexBuffer vb;

    vb.setType(rend::VertexBuffer::INDEXEDTRIANGLELIST);
    vb.appendVertices(vertices, indices);

    auto material = make_shared<rend::Material>();
    material->plainColor = rend::Color3(255, 255, 255);
    material->ambientColor = rend::Color3(255, 255, 255);
    material->diffuseColor = rend::Color3(255, 255, 255);
    material->shadeMode = rend::Material::SM_FLAT;
    material->sideType = rend::Material::ONE_SIDE;

    vb.setMaterial(material);

    auto mesh = make_shared<rend::Mesh>();
    mesh->appendSubmesh(vb);

    setMesh(mesh);
}

}

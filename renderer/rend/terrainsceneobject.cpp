/*
 * terrainsceneobject.cpp
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#include "stdafx.h"

#include "terrainsceneobject.h"
#include "texture.h"
#include "mesh.h"
#include "vertexbuffer.h"

namespace rend
{

TerrainSceneObject::TerrainSceneObject(float width, float height, float vertScale,
                                       const sptr(Texture) heightMap,
                                       const sptr(Texture) texture)
{
    if (!heightMap)
        return;

    // set name
    setName(std::string("terrain_") + heightMap->getName());

    int columns = heightMap->width();
    int rows = heightMap->height();

    float colStep = width / (float)(columns - 1);
    float rowStep = height / (float)(rows - 1);

    float colStepText = 0.0, rowStepText = 0.0;
    if (texture)
    {
        colStepText = ((float)texture->width() - 1) / (columns - 1.0);
        rowStepText = ((float)texture->height() - 1) / (rows - 1.0);
    }

    // store all vertices
    std::vector<math::vertex> vertices;      // FIXME: allocate mem before
    std::vector<math::vec2> uvs;
    for (int currRow = 0; currRow < rows; currRow++)
    {
        for (int currCol = 0; currCol < columns; currCol++)
        {
            math::vertex v;

            v.p.x = currCol * colStep - (width / 2.0f);      // (0;0) point is the center of the map
            v.p.z = currRow * rowStep - (height / 2.0f);

            // XYNTA:
            v.p.y = (float)heightMap->at(currCol, currRow)[RED] / 255.0f;
            v.p.y *= vertScale;

            if (texture)
            {
                math::vec2 uv;
                uv.x = currCol * colStepText;
                uv.y = currRow * rowStepText;

                uv.x /= float(texture->width() - 1.);   // normalize
                uv.y /= float(texture->height() - 1.);   // normalize

                uvs.push_back(uv);
            }

            vertices.push_back(v);
        }
    }

    // create triangles
    std::vector<int> indices;
    std::vector<int> uvInds;
    for (int poly = 0; poly < ((columns - 1) * (rows - 1)); poly++)
    {
        int basePolyInd = (poly % (columns - 1)) + (columns * (poly / (columns - 1)));

        indices.push_back(basePolyInd);
        indices.push_back(basePolyInd + columns);
        indices.push_back(basePolyInd + columns + 1);

        indices.push_back(basePolyInd);
        indices.push_back(basePolyInd + columns + 1);
        indices.push_back(basePolyInd + 1);

        if (texture)
        {
            uvInds.push_back(basePolyInd);
            uvInds.push_back(basePolyInd + columns);
            uvInds.push_back(basePolyInd + columns + 1);

            uvInds.push_back(basePolyInd);
            uvInds.push_back(basePolyInd + columns + 1);
            uvInds.push_back(basePolyInd + 1);
        }
    }

    VertexBuffer vb;

    vb.setType(rend::VertexBuffer::INDEXEDTRIANGLELIST);
    if (texture)
        vb.appendVertices(vertices, indices, uvs, uvInds);
    else
        vb.appendVertices(vertices, indices);

    auto material = std::make_shared<rend::Material>();
    material->plainColor = rend::Color3(255, 255, 255);
    material->ambientColor = rend::Color3(255, 255, 255);
    material->diffuseColor = rend::Color3(255, 255, 255);

    if (texture)
    {
        material->texture = texture;
        material->shadeMode = rend::Material::SM_TEXTURE;
    }
    else
        material->shadeMode = rend::Material::SM_GOURAUD;

    material->sideType = rend::Material::ONE_SIDE;

    vb.setMaterial(material);

    auto mesh = std::make_shared<rend::Mesh>();
    mesh->appendSubmesh(vb);

    setMesh(mesh);
}

}
